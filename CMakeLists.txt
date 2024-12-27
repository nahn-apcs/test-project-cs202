# cmake_minimum_required(VERSION 3.14)
# project(MyGame LANGUAGES CXX)

# # Tùy chọn và cấu hình project
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# option(ENABLE_TESTS "Enable building of tests" ON)

# # Nhúng các module cần thiết
# include(FetchContent)

# # Tìm kiếm SFML
# find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# # Fetch JSON library
# FetchContent_Declare(
#     json
#     URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
# )
# FetchContent_MakeAvailable(json)

# # Tìm các file mã nguồn
# file(GLOB SRCS 
#     ${CMAKE_SOURCE_DIR}/src/*.cpp
#     ${CMAKE_SOURCE_DIR}/src/gui/*.cpp
# )

# # Tạo executable
# add_executable(game ${SRCS})

# # Liên kết các thư viện
# target_link_libraries(game PRIVATE 
#     sfml-graphics sfml-window sfml-system sfml-audio 
#     SQLiteCpp sqlite3 
#     nlohmann_json::nlohmann_json
# )

# # Xử lý đặc thù cho Unix
# if (UNIX)
#     target_link_libraries(game PRIVATE pthread dl)
# endif()

# # Thêm các tests nếu được bật
# if (ENABLE_TESTS)
#     add_subdirectory(tests)
# endif()

# # Cài đặt
# install(TARGETS game RUNTIME DESTINATION bin)

cmake_minimum_required(VERSION 3.11)
project(CS202Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Tải thư viện SFML từ GitHub
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.2  # Thay đổi phiên bản nếu cần
)

# Tải về và thêm thư viện
FetchContent_MakeAvailable(SFML)

# Fetch SQLiteCpp
include(FetchContent)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG 3.3.2
    GIT_CONFIG "core.autocrlf=false"
)
FetchContent_GetProperties(SQLiteCpp)

if(NOT SQLiteCpp_POPULATED)
    FetchContent_Populate(SQLiteCpp)
    add_subdirectory(${sqlitecpp_SOURCE_DIR} ${sqlitecpp_BINARY_DIR})
endif()

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Tạo danh sách chứa đầy đủ các file .cpp
# Liệt kê hết những folder mà mình có file cpp
# để khi chạy có thể tìm thấy hết file
file(GLOB SRCS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/GameLogic/*.cpp
    ${CMAKE_SOURCE_DIR}/src/GameState/*.cpp
)

add_executable(game ${SRCS})

# link thư viện
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio SQLiteCpp sqlite3 nlohmann_json::nlohmann_json)

if (UNIX)
    target_link_libraries(game PRIVATE pthread dl)
endif()

target_compile_features(game PRIVATE cxx_std_17)

#thêm các folder vào đây
target_include_directories(game PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/GameLogic
    ${CMAKE_SOURCE_DIR}/src/GameState
    ${CMAKE_SOURCE_DIR}/header
    ${CMAKE_SOURCE_DIR}/header/GameLogic
    ${CMAKE_SOURCE_DIR}/header/GameState
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_SOURCE_DIR}/resources/Asset
    ${CMAKE_SOURCE_DIR}/resources/Asset/Font
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/CompleteLevel
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Game
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/GameOver
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Guide
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Level
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Menu
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Pause
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Setting
    ${CMAKE_SOURCE_DIR}/resources/Asset/Textures/Winning
    ${CMAKE_SOURCE_DIR}/resources/Audio
    ${CMAKE_SOURCE_DIR}/resources/boss minotaur
    ${CMAKE_SOURCE_DIR}/resources/boss minotaur/main
    ${CMAKE_SOURCE_DIR}/resources/font
    ${CMAKE_SOURCE_DIR}/resources/Level1
    ${CMAKE_SOURCE_DIR}/resources/Level2
    ${CMAKE_SOURCE_DIR}/resources/Level3
    ${CMAKE_SOURCE_DIR}/resources/projectiles
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet/master
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet/object
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet/pig
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet/pig/Pig_enemy_sprite_sheet
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet/wukong
    ${CMAKE_SOURCE_DIR}/resources/sprite_sheet/wukong/old
    ${CMAKE_SOURCE_DIR}/resources/wukong16bit
    ${CMAKE_SOURCE_DIR}/resources/wukong16bit/iloveimg-resized


)

if(WIN32)
    add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)
endif()


install(TARGETS game)
