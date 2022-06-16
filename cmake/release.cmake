add_library(
    release_env
    INTERFACE
)

target_include_directories(
    release_env
    INTERFACE
        env/release
)

include(cmake/release/link.cmake)
