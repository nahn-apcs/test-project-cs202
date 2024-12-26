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
project(GroupProject7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Tải thư viện SFML từ GitHub
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1  # Thay đổi phiên bản nếu cần
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
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/GameState/*.cpp
        ${CMAKE_SOURCE_DIR}/src/GameLogic/*.cpp

)

add_executable(game ${SRCS} 

"header/GameLogic/constant.h"
"header/GameLogic/tile.h"
"header/GameLogic/render.h"
"src/GameLogic/tile.cpp"
"src/GameLogic/Map.cpp"
"header/GameLogic/Character.h"
"src/GameLogic/Character.cpp"
"header/GameLogic/Physics.h"
"src/GameLogic/Physics.cpp"
"header/GameLogic/Coin.h"
"src/GameLogic/Coin.cpp"
"header/GameLogic/Animation.h"
"header/GameLogic/Monster.h"
"src/GameLogic/Monster.cpp"
"header/GameLogic/MonsterAnimation.h"
"src/GameLogic/MonsterAnimation.cpp"
"header/GameLogic/DrawEngine.h"
"src/GameLogic/DrawEngine.cpp"
"header/GameLogic/ObjectAnimation.h"
"header/GameLogic/BlockAnimation.h"
"src/GameLogic/CoinAnimation.cpp"
"header/GameLogic/Block.h"
"src/GameLogic/Block.cpp"
"header/GameLogic/BlockState.h"
"src/GameLogic/BlockState.cpp"
"header/GameLogic/Projectile.h"
"header/GameLogic/ProjectileAnimation.h"
"src/GameLogic/Projectile.cpp"
"src/GameLogic/ProjectileAnimation.cpp"
"header/GameLogic/Item.h"
"src/GameLogic/Item.cpp"
"src/GameLogic/AudioManagement.cpp"

# Source files
"src/GameState/Animation.cpp"
"src/GameState/Application.cpp"
"src/GameState/Button.cpp"
"src/GameState/Component.cpp"
"src/GameState/Container.cpp"
"src/GameState/GuideState.cpp"
"src/GameState/LevelState.cpp"
"src/GameState/main.cpp"
"src/GameState/MenuState.cpp"
"src/GameState/State.cpp"
"src/GameState/StateStack.cpp"
"src/GameState/Utility.cpp"

# Header files
"header/GameState/Animation.hpp"
"header/GameState/Application.hpp"
"header/GameState/Button.hpp"
"header/GameState/Component.hpp"
"header/GameState/Container.hpp"
"header/GameState/GuideState.hpp"
"header/GameState/LevelState.hpp"
"header/GameState/MenuState.hpp"
"header/GameState/State.hpp"
"header/GameState/StateStack.hpp"
"header/GameState/Utility.hpp"

"src/GameState/GameState.cpp"
"header/GameLogic/Boss.h"
"src/GameLogic/Boss.cpp"
"src/GameState/PauseState.cpp"
"src/GameState/LevelManager.cpp"
"src/GameState/WaitingState.cpp"
"src/GameState/TransitionState.cpp"
"src/GameState/BGNode.cpp"
"src/GameState/BGObject.cpp"
"src/GameState/Command.cpp"
"src/GameState/CommandQueue.cpp"
"src/GameState/GameOverState.cpp"
"src/GameState/LevelCompleteState.cpp"
"src/GameState/MusicPlayer.cpp"
"src/GameState/SceneNode.cpp"
"src/GameState/SettingState.cpp"
"src/GameState/SoundPlayer.cpp"
"src/GameState/TextNode.cpp"
"src/GameState/WinningState.cpp"
)

# link thư viện
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio SQLiteCpp sqlite3 nlohmann_json::nlohmann_json)

if (UNIX)
    target_link_libraries(game PRIVATE pthread dl)
endif()

target_compile_features(game PRIVATE cxx_std_17)

#thêm các folder vào đây
target_include_directories(game PRIVATE
    #${CMAKE_SOURCE_DIR}/include
    header
    resources
    header/GameState
    header/GameLogic
)
if(WIN32)
    add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)
endif()
# Copy images directory
add_custom_target(copy_resources_images ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources

)
add_dependencies(game copy_resources_images)

install(TARGETS game)
