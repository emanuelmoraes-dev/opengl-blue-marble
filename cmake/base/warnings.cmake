option(OPT_WARNS_AS_ERR "The warnings are considered as error" OFF)

if (USING_MSVC)
    set(WARNS
        /W4
        /wd4201
        /wd4100
    )

    set(WARNS_AS_ERR
        /WX
    )
elseif (USING_CLANG)
    set(WARNS
        -Wall
        -Wextra
        -Wpedantic  # Warn if non-standard C is used.
    )

    set(WARNS_AS_ERR
        -Werror
    )
elseif (USING_GCC)
    set(WARNS
        -Wall
        -Wextra
        -Wpedantic  # Warn if non-standard C is used.
    )

    set(WARNS_AS_ERR
        -Werror
    )
endif()

target_compile_options(
    base
    INTERFACE
        ${WARNS}
)

if (OPT_WARNS_AS_ERR)
    target_compile_options(
        base
        INTERFACE
            ${WARNS_AS_ERR}
    )
endif()
