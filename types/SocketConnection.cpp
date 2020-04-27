#include "SocketConnection.h"
#include "SocketPacket.h"
#include "SocketPacketIStream.h"
#include "SocketPacketOStream.h"
#include "../packets/Packets.h"

#include <iostream>

#define RECV_SIZE 1024

#define OFFLINE_MODE

SocketConnection::SocketConnection(SOCKET socket, ServerEnc* encSrv) :
	Socket(socket),
	EncSrv(encSrv),
	Thread(&SocketConnection::ConnectionThread, this),
	RecvBuffer(new char[RECV_SIZE]),
	RecvInd(0),
	CompressionEnabled(false),
	EncryptionEnabled(false),
	EncCtx(nullptr),
	State(ConnectionState::Handshaking)
{

}

SocketConnection::~SocketConnection() {
	Flag.cancel();
	if (EncCtx) {
		EncSrv->Disconnect(EncCtx);
	}
	//delete Thread;
}

int SocketConnection::Write(const char* data, uint32_t dataLength) {
	if (EncryptionEnabled) {
		auto encrData = std::make_unique<char[]>(dataLength);
		int encrLength;
		if (!EncSrv->EncryptData(EncCtx, data, dataLength, encrData.get(), &encrLength)) {

		}
		return send(Socket, encrData.get(), encrLength, 0);
	}
	else {
		return send(Socket, data, dataLength, 0);
	}
}

bool SocketConnection::WriteByte(uint8_t value) {
	if (EncryptionEnabled) {
		char encrData;
		int encrLength;
		if (!EncSrv->EncryptData(EncCtx, (char*)&value, 1, &encrData, &encrLength)) {

		}
		return send(Socket, &encrData, encrLength, 0) == 1;
	}
	else {
		return send(Socket, (const char*)&value, 1, 0) == 1;
	}
}

int SocketConnection::Read(char* data, uint32_t dataLength) {
	if (dataLength == 0) return 0;
	int bytesRead = 0;
	while (dataLength > 0) {
		if (RecvInd + dataLength > RecvSize) {
			memcpy(data + bytesRead, RecvBuffer + RecvInd, RecvSize - RecvInd);
			bytesRead += RecvSize - RecvInd;
			dataLength -= RecvSize - RecvInd;
			if (!RefillBuffer()) {
				return bytesRead;
			}
		}
		else {
			memcpy(data + bytesRead, RecvBuffer + RecvInd, dataLength);
			RecvInd += dataLength;
			bytesRead += dataLength;
			dataLength = 0;
		}
	}
	return bytesRead;
}

uint8_t SocketConnection::ReadByte()
{
	if (RecvInd < RecvSize) {
		return RecvBuffer[RecvInd++];
	}
	else {
		if (!RefillBuffer()) {
			return 0;
		}
		return ReadByte();
	}
}

uint8_t SocketConnection::PeekByte() {
	if (RecvInd < RecvSize) {
		return RecvBuffer[RecvInd];
	}
	return 0;
}

int32_t SocketConnection::GetAvailableBufferSize() {
	return -1;
}

bool SocketConnection::RefillBuffer() {
	RecvSize = recv(Socket, RecvBuffer, RECV_SIZE, 0);
	RecvInd = 0;
	return RecvSize;
}

void SocketConnection::HandlePacket(SocketPacket& packet)
{
	std::cout << "Packet Size: " << packet.Length.Value << std::endl
		<< "Packet ID: " << packet.PacketID.Value << std::endl << std::endl;

	SocketPacketIStream packetStream(packet.PacketData.get(), packet.Length.Value - packet.PacketID.GetSize());
	switch (State)
	{
	case ConnectionState::Handshaking:
		switch (packet.PacketID.Value)
		{
		case 0x00:
		{
			SBHandshake handshake;
			packetStream >> handshake;
			switch (handshake.NextState.Value) {
			case 1:
				State = ConnectionState::Status;
				break;
			case 2:
				State = ConnectionState::Login;
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	case ConnectionState::Status:
		switch (packet.PacketID.Value)
		{
		case 0x00:
		{
			SBRequest request;
			packetStream >> request;

			CBResponse response;
			response.JsonString = SocketString(R"({"version":{"name":"Fortnite 13.00","protocol":578},"players":{"max":100,"online":1,"sample":[{"name":"Only cool kids can join","id":"4566e69f-c907-48ee-8d71-d7ba5aa00d20"}]},"description":{"text":"use code furry please"}})");
			response.JsonLength.Value = response.JsonString.Length.Value;
			SocketPacketOStream os(0x00);
			os << response;
			*this << os;
			break;
		}
		case 0x01:
		{
			SBPing ping;
			packetStream >> ping;

			CBPong pong;
			pong.Payload.Value = ping.Payload.Value;
			SocketPacketOStream os(0x01);
			os << pong;
			*this << os;
			break;
		}
		default:
			break;
		}
		break;
	case ConnectionState::Login:
		switch (packet.PacketID.Value)
		{
		case 0x00:
		{
			SBLoginStart packet;
			packetStream >> packet;

#ifndef OFFLINE_MODE
			CBEncrReq req;
			EncCtx = Server->EncData.GetEncrReq(req);
			SocketPacketOStream os(0x01);
			os << req;
			*this << os;
#endif
			CBLoginSuccess req;
			req.Username.SetValue(packet.Name.Data.get());
			req.UUID.SetValue("324446f0-abee-438a-8089-7f71a38afa5c");

			SocketPacketOStream os(0x02);
			os << req;
			*this << os;

			State = ConnectionState::Play;
		}
		case 0x01:
		{
#ifndef OFFLINE_MODE
			SBEncrResp packet;
			packetStream >> packet;

			if (!Server->EncData.HandleEncrResp(EncCtx, packet)) {

			}
			EncryptionEnabled = true;

			//CBSetCompr req;
			//req.Threshold.Value = 128;

			CBLoginSuccess req;
			req.Username.SetValue("AsrielD");
#endif
		}
		default:
			break;
		}
		break;
	case ConnectionState::Play:
		switch (packet.PacketID.Value)
		{
		case 0x00:
		{
			break;
		}
		case 0x01:
		{
			break;
		}
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void SocketConnection::ConnectionThread() {
	char recvBuffer[RECV_SIZE];
	while (!Flag.cancelled()) {
		if (State == ConnectionState::Handshaking || State == ConnectionState::Status) {
			if (PeekByte() == 0xFE) {
				printf("LEGACY PING!!");
				break;
			}
		}
		SocketPacket packet;
		if (!CompressionEnabled) {
			*this >> packet.Length;
			*this >> packet.PacketID;
			auto dataSize = packet.Length.Value - packet.PacketID.GetSize();
			if (dataSize == -1 || !RecvSize) {
				printf("bruh?\n");
				break;
			}
			packet.PacketData = std::make_unique<char[]>(dataSize);
			Read(packet.PacketData.get(), dataSize);
		}
		HandlePacket(packet);
	}
	shutdown(Socket, SD_BOTH);
}