cmake_minimum_required (VERSION 3.8)

project (CMine)

aux_source_directory(. FILE_SOURCES)
aux_source_directory(types TYPES_FILE_SOURCES)
aux_source_directory(encryption ENCRYPTION_FILE_SOURCES)

add_executable (CMine ${ENCRYPTION_FILE_SOURCES} ${TYPES_FILE_SOURCES} ${FILE_SOURCES})

set_property(TARGET CMine PROPERTY CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

target_link_libraries(CMine PRIVATE Ws2_32 OpenSSL::SSL OpenSSL::Crypto Crypt32)