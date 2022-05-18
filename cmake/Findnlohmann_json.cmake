include(CMakeFindDependencyMacro)

if (NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION)
    set(${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION "3.10.5")
endif (NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION)

message(CHECK_START "Searching for ${CMAKE_FIND_PACKAGE_NAME}")

#===========================#
#=====# Local install #=====#
#===========================#

find_package(${CMAKE_FIND_PACKAGE_NAME}
    ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION}
    CONFIG
)

if (${CMAKE_FIND_PACKAGE_NAME}_FOUND)
    message(CHECK_PASS "local")
    return()
endif (${CMAKE_FIND_PACKAGE_NAME}_FOUND)

#===========================#
#=====# Clone project #=====#
#===========================#

include(FetchContent)

FetchContent_Declare(${CMAKE_FIND_PACKAGE_NAME}
    URL "https://github.com/nlohmann/json/archive/refs/tags/v${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION}.tar.gz"
)

FetchContent_GetProperties(${CMAKE_FIND_PACKAGE_NAME})

if (NOT ${CMAKE_FIND_PACKAGE_NAME}_POPUlATED)
    FetchContent_Populate(${CMAKE_FIND_PACKAGE_NAME})

    add_subdirectory(
        ${${CMAKE_FIND_PACKAGE_NAME}_SOURCE_DIR}
        ${${CMAKE_FIND_PACKAGE_NAME}_BINARY_DIR}
        EXCLUDE_FROM_ALL
    )
endif (NOT ${CMAKE_FIND_PACKAGE_NAME}_POPUlATED)

set(${CMAKE_FIND_PACKAGE_NAME}_FOUND TRUE)
message(CHECK_PASS "cloned")
