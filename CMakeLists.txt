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
    ${CMAKE_SOURCE_DIR}/src/SourceMenu/*.cpp
)

add_executable(game ${SRCS} "header/constant.h" "header/tile.h" "header/render.h" "src/tile.cpp" "header/loadTiles.h" "src/Map.cpp" "header/Character.h" "src/Character.cpp" "header/Physics.h" "src/Physics.cpp" "header/Coin.h" "src/Coin.cpp" "header/Animation.h" "header/Monster.h" "src/Monster.cpp" "header/MonsterAnimation.h" "src/MonsterAnimation.cpp"  "header/DrawEngine.h" "src/DrawEngine.cpp" "header/ObjectAnimation.h" "header/BlockAnimation.h" "src/CoinAnimation.cpp" "header/Block.h"  "src/Block.cpp" "header/BlockState.h" "src/BlockState.cpp" "header/Projectile.h" "header/ProjectileAnimation.h" "src/Projectile.cpp" "src/ProjectileAnimation.cpp" "header/Item.h" "src/Item.cpp" "src/AudioManagement.cpp" 
    # Source files
"src/SourceMenu/Animation.cpp"
"src/SourceMenu/Application.cpp"
"src/SourceMenu/Button.cpp"
"src/SourceMenu/Component.cpp"
"src/SourceMenu/Container.cpp"
"src/SourceMenu/GuideState.cpp"
"src/SourceMenu/LevelState.cpp"
"src/SourceMenu/main.cpp"
"src/SourceMenu/MenuState.cpp"
"src/SourceMenu/State.cpp"
"src/SourceMenu/StateStack.cpp"
"src/SourceMenu/Utility.cpp"

# Header files
"header/Include/Animation.hpp"
"header/Include/Application.hpp"
"header/Include/Button.hpp"
"header/Include/Component.hpp"
"header/Include/Container.hpp"
"header/Include/GuideState.hpp"
"header/Include/LevelState.hpp"
"header/Include/MenuState.hpp"
"header/Include/State.hpp"
"header/Include/StateStack.hpp"
"header/Include/Utility.hpp"

 "src/SourceMenu/GameState.cpp")

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
    Asset
    header/Include
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
    ${CMAKE_SOURCE_DIR}/Asset
    ${CMAKE_BINARY_DIR}/Asset
)
add_dependencies(game copy_resources_images)

install(TARGETS game)
