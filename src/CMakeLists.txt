add_executable(main)

target_sources(
    main
    PRIVATE
        main.cc
)

target_compile_features(
    main
    PUBLIC
        cxx_std_17
)
