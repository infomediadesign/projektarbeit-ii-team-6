cmake_minimum_required(VERSION 3.19)

project("Crimson-Mine"
	DESCRIPTION "A roguelike dungeon crawler in a western fantasy world"
	HOMEPAGE_URL "https://github.com/infomediadesign/projektarbeit-ii-team-6"
)

# Custom Find<module>.cmake
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME})

file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*")
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_FILES} "src/Objects/Torch.h" "src/Objects/Torch.cpp")
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/src" PREFIX "Source" FILES ${PROJECT_SOURCE_FILES})

add_custom_target(${PROJECT_NAME}_assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/assets" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
	COMMENT "Copying asset directory to project output"
)

file(GLOB_RECURSE PROJECT_ASSET_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/assets/*")
target_sources(${PROJECT_NAME}_assets PRIVATE ${PROJECT_ASSET_FILES} "src/Objects/Torch.h" "src/Objects/Torch.cpp")
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/assets" PREFIX "Assets" FILES ${PROJECT_ASSET_FILES})

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_assets)

#======================#
#=====# Metadata #=====#
#======================#

# Language standard & features
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS FALSE)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/assets")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

#==========================#
#=====# Dependencies #=====#
#==========================#

find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE "raylib")

find_package(nlohmann_json REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE "nlohmann_json::nlohmann_json")

#==========================#
#=====# Installation #=====#
#==========================#

install(TARGETS
	${PROJECT_NAME}
	DESTINATION .
)

install(DIRECTORY
	"${PROJECT_SOURCE_DIR}/assets"
	DESTINATION .
)

install(FILES
	"${PROJECT_SOURCE_DIR}/LICENSE"
	DESTINATION .
)
