add_library(
    release_env
    INTERFACE
)

target_include_directories(
    release_env
    INTERFACE
        env/release
)

target_link_libraries(
    BlueMarble
    PRIVATE
        optimized release_env
)
