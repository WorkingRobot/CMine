#include "SocketConnection.h"
#include "SocketPacket.h"
#include "SocketPacketIStream.h"
#include "SocketPacketOStream.h"
#include "../packets/Packets.h"

#include <iostream>

#define OFFLINE_MODE
#define RECV_SIZE 1024

#define SEND_PACKET(packet) \
{ \
	SocketPacketOStream os(decltype(packet)::Id); \
	os << packet; \
	*this << os; \
}

#define READ_PACKET(packetType) \
	packetType packet; \
	packetStream >> packet;

SocketConnection::SocketConnection(SOCKET socket, ServerEnc* encSrv) :
	Socket(socket),
	EncSrv(encSrv),
	Thread(&SocketConnection::ConnectionThread, this),
	RecvBuffer(new char[RECV_SIZE]),
	RecvInd(0),
	RecvSize(0),
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
	printf("Refilling to %d\n", RecvSize);
	return RecvSize != -1 && RecvSize;
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
			InitLogin();
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
		case SBPluginMessage::Id:
		{
			READ_PACKET(SBPluginMessage);
			auto channel = packet.Channel.GetString();
			auto data = packet.Data.CreateStream();
			if (channel == "minecraft:brand") {
				SocketString brand;
				data >> brand;
				std::cout << "Brand: " << brand << std::endl;
			}
			else if (channel == "minecraft:register") {
				std::cout << "Register: " << packet.Data << std::endl;
			}
			else if (channel == "minecraft:unregister") {
				std::cout << "Unegister: " << packet.Data << std::endl;
			}
			else {
				std::cout << "New message from " << packet.Channel << ":\n" << packet.Data << "\n";
			}
		}
		break;
		case SBClientSettings::Id:
		{
			READ_PACKET(SBClientSettings);
			std::cout << "Client Settings:\n"
				<< "Chat Mode: " << std::to_string(packet.ChatMode) << "\n"
				<< "Color: " << (packet.ColorEnabled ? "Yes" : "No") << "\n"
				<< "Locale: " << packet.Locale << "\n"
				<< "Main Hand: " << (packet.MainHand ? "Right" : "Left") << "\n"
				<< "View Distance: " << std::to_string(packet.ViewDistance) << "\n"
				<< "Skin Parts: " << std::to_string(packet.SkinParts) << "\n";

			ContinueLogin();
		}
		break;
		case SBTeleportConfirm::Id:
		{
			READ_PACKET(SBTeleportConfirm);
			std::cout << "Teleport Confirm: Id " << std::to_string(packet.TeleportId) << "\n";
		}
		break;
		case SBPlayerPosRot::Id:
		{
			READ_PACKET(SBPlayerPosRot);
			std::cout << "Confirm PosRot:\n"
				<< "Position: (" << std::to_string(packet.PosX) << ", "
				<< std::to_string(packet.FeetY) << ", "
				<< std::to_string(packet.PosZ) << ")\n"
				<< "Angle: (" << std::to_string(packet.Yaw) << ", "
				<< std::to_string(packet.Pitch) << ")\n"
				<< "OnGround: " << (packet.OnGround ? "Yes" : "No") << "\n";
		}
		break;
		case SBClientStatus::Id:
		{
			READ_PACKET(SBClientStatus);
			std::cout << "Client Status:\n" << (packet.ActionId ? "Respawning" : "Stats!") << "\n";
		}
		break;
		}
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
				printf("No more data size, disconnecting\n");
				break;
			}
			packet.PacketData = std::make_unique<char[]>(dataSize);
			Read(packet.PacketData.get(), dataSize);
		}
		HandlePacket(packet);
	}
	shutdown(Socket, SD_BOTH);
}

void SocketConnection::InitLogin()
{
	{
		CBJoinGame packet;
		packet.EntityId = 14;
		packet.Gamemode = 1;
		packet.Dimension = 0;
		packet.HashedSeed = 0;
		packet.MaxPlayers = 0;
		packet.LevelType = "default";
		packet.ViewDistance = 2;
		packet.ReducedDebugInfo = false;
		packet.EnableRespawnScreen = true;

		SEND_PACKET(packet);
	}
	{
		CBPluginMessage packet;
		packet.Channel = "minecraft:brand";
		packet.Data = std::string("CMine");

		SEND_PACKET(packet);
	}
	{
		CBServerDifficulty packet;
		packet.Difficulty = 0;
		packet.Locked = true;

		SEND_PACKET(packet);
	}
	{
		CBPlayerAbilities packet;
		packet.Flags = 0x01 | 0x08; // invulnerable, creative mode, no flying
		packet.FlySpeed = .05f;
		packet.FovModifier = .1f;

		SEND_PACKET(packet);
	}
}

void SocketConnection::ContinueLogin() {
	{
		CBHeldItemChange packet;
		packet.Slot = 0;

		SEND_PACKET(packet);
	}
	{
		CBDeclareRecipes packet;
		
		SEND_PACKET(packet);
	}
	{
		CBTags packet;
		// unknown what to send here

		SEND_PACKET(packet);
	}
	{
		CBEntityStatus packet;
		packet.EntityId = 14;
		packet.EntityStatus = 28; // set to op level 4
		// unknown what to send here

		SEND_PACKET(packet);
	}
	{
		CBDeclareCommands packet;
		packet.RootInd = 0;

		//SEND_PACKET(packet);
	}
	{
		CBUnlockRecipes packet;
		// unknown what to send here

		//SEND_PACKET(packet);
	}
	{
		CBPlayerPosRot packet;
		packet.Flags = 0; // all absolute
		packet.PosX = 0;
		packet.PosY = 30;
		packet.PosZ = 0;
		packet.Yaw = 0;
		packet.Pitch = 0; // straight ahead
		packet.TeleportId = 12;

		SEND_PACKET(packet);
	}
	{
		CBPlayerInfo packet;
		packet.Action = 0;
		CBPlayerInfo::Player player;
		player.Uuid = SocketGUID(30, 20, 10, 0);
		player.Name = "AsrielD";
		player.Gamemode = 1;
		player.Ping = 0;

		SEND_PACKET(packet);
	}
	{
		CBPlayerInfo packet;
		packet.Action = 2;
		CBPlayerInfo::Player player;
		player.Uuid = SocketGUID(30, 20, 10, 0);
		player.Ping = 1;

		SEND_PACKET(packet);
	}
	{
		CBUpdateViewPos packet;
		packet.ChunkX = 0;
		packet.ChunkZ = 0;

		SEND_PACKET(packet);
	}
	{
		CBUpdateLight packet;
		packet.ChunkX = 0;
		packet.ChunkZ = 0;
		
		//SEND_PACKET(packet); deal with this shit when i read a world file lol
	}
	{
		CBChunkData packet;
		packet.ChunkX = 0;
		packet.ChunkZ = 0;

		//SEND_PACKET(packet); deal with this shit when i read a world file lol
	}
	{
		CBWorldBorder packet;
		packet.Action = 3;
		packet.PosX = 0;
		packet.PosZ = 0;
		packet.OldDiameter = 4000;
		packet.NewDiameter = 4000;
		packet.Speed = 0;
		packet.PortalTpBoundary = 29999984;
		packet.WarningTime = 0;
		packet.WarningBlocks = 30;

		SEND_PACKET(packet);
	}
	{
		CBSpawnPosition packet;
		packet.Location.SetValue(0, 30, 0); // bed spawn

		SEND_PACKET(packet);
	}
	{
		CBPlayerPosRot packet;
		packet.Flags = 0; // all absolute
		packet.PosX = 0;
		packet.PosY = 30;
		packet.PosZ = 0;
		packet.Yaw = 0;
		packet.Pitch = 0; // straight ahead
		packet.TeleportId = 13;

		SEND_PACKET(packet);
	}
}