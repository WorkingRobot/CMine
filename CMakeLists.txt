cmake_minimum_required (VERSION 3.8)

project (CMine)

aux_source_directory(. FILE_SOURCES)
aux_source_directory(types TYPES_FILE_SOURCES)
aux_source_directory(encryption ENCRYPTION_FILE_SOURCES)
aux_source_directory(data DATA_FILE_SOURCES)
aux_source_directory(nbt NBT_FILE_SOURCES)

add_executable (CMine ${NBT_FILE_SOURCES} ${DATA_FILE_SOURCES} ${ENCRYPTION_FILE_SOURCES} ${TYPES_FILE_SOURCES} ${FILE_SOURCES})

set_property(TARGET CMine PROPERTY CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

target_link_libraries(CMine PRIVATE Ws2_32 OpenSSL::SSL OpenSSL::Crypto Crypt32)