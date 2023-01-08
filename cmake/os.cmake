if (WIN32)
    # windows

    set_target_properties(
        BlueMarble
        PROPERTIES 
            LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
    )
endif()
