add_library(
    debug_env
    INTERFACE
)

target_include_directories(
    debug_env
    INTERFACE
        env/debug
)

include(cmake/debug/link.cmake)
