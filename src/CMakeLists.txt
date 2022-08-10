
# Set version.h
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config/version.hpp.in ${CMAKE_BINARY_DIR}/version.hpp)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

FIND_PACKAGE(spdlog REQUIRED)

# Set dps_header_files
SET(dps_header_files
        dps.hpp
        macros.hpp
#        message_t.hpp
        socket_t.hpp
        loop_thread_t.hpp
        utils.hpp
        )

# Set dps_source_files
SET(dps_source_files
        dps.cpp
#        message_t.cpp
        socket_t.cpp
        loop_thread_t.cpp
        utils.cpp
        )

ADD_LIBRARY(dps SHARED
        "${dps_source_files}"
        "${dps_header_files}"
        )

SET_TARGET_PROPERTIES(dps PROPERTIES
        VERSION ${CMAKE_PROJECT_VERSION}
        SOVERSION 1
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        PUBLIC_HEADER dps.hpp)

TARGET_INCLUDE_DIRECTORIES(dps
        PUBLIC
        "${CMAKE_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

TARGET_LINK_LIBRARIES(dps
        spdlog::spdlog
        )

# TODO
#install(TARGETS dps
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main
        dps)




