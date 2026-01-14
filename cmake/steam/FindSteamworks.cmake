# FindSteamworks.cmake
#
# Usage:
#   find_package(Steamworks)
#
# Variables:
#   Steamworks_FOUND
#   Steamworks_VERSION
#   Steamworks_INCLUDE_DIRS
#   Steamworks_LIBRARIES
#
# Targets:
#   Steamworks::Steamworks

include(FindPackageHandleStandardArgs)

# ------------------------------------------------------------
# User override. 
# Use cmake -DSTEAMWORKS_ROOT="C:/SDKs/steamworks_sdk_163" ..
# ------------------------------------------------------------

set(STEAMWORKS_ROOT "" CACHE PATH
    "Path to Steamworks SDK root (steamworks_sdk_###)"
)

# ------------------------------------------------------------
# Auto-detection. If the user did not specify STEAMWORKS_ROOT, 
# we search for a directory named steamworks_sdk_* in the root 
# of the project.
# ------------------------------------------------------------

if(NOT STEAMWORKS_ROOT)
    file(GLOB _STEAMWORKS_CANDIDATES
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/steamworks_sdk_*"
    )

    list(LENGTH _STEAMWORKS_CANDIDATES _sdk_count)

    if(_sdk_count EQUAL 1)
        set(STEAMWORKS_ROOT
            "${CMAKE_CURRENT_SOURCE_DIR}/${_STEAMWORKS_CANDIDATES}"
        )
    elseif(_sdk_count GREATER 1)
        message(FATAL_ERROR
            "Multiple Steamworks SDK directories found:\n"
            "  ${_STEAMWORKS_CANDIDATES}\n"
            "Please specify STEAMWORKS_ROOT manually."
        )
    endif()
endif()

# ------------------------------------------------------------
# Validate SDK structure
# ------------------------------------------------------------

if(STEAMWORKS_ROOT AND EXISTS "${STEAMWORKS_ROOT}")
    set(_STEAMWORKS_INCLUDE_DIR
        "${STEAMWORKS_ROOT}/sdk/public/steam"
    )

    set(_STEAMWORKS_LIB_DIR
        "${STEAMWORKS_ROOT}/sdk/redistributable_bin"
    )

    if(WIN32)
        set(_STEAMWORKS_LIBRARY
            "${_STEAMWORKS_LIB_DIR}/win64/steam_api64.lib"
        )
        set(_STEAMWORKS_RUNTIME_DLL
            "${_STEAMWORKS_LIB_DIR}/win64/steam_api64.dll"
        )
    elseif(APPLE)
        set(_STEAMWORKS_LIBRARY
            "${_STEAMWORKS_LIB_DIR}/osx/libsteam_api.dylib"
        )
    elseif(UNIX)
        set(_STEAMWORKS_LIBRARY
            "${_STEAMWORKS_LIB_DIR}/linux64/libsteam_api.so"
        )
    endif()
endif()

# ------------------------------------------------------------
# Version extraction
# ------------------------------------------------------------

if(STEAMWORKS_ROOT)
    get_filename_component(_sdk_dir_name "${STEAMWORKS_ROOT}" NAME)
    string(REGEX REPLACE
        "^steamworks_sdk_"
        ""
        Steamworks_VERSION
        "${_sdk_dir_name}"
    )
endif()

# ------------------------------------------------------------
# Handle result
# ------------------------------------------------------------

find_package_handle_standard_args(Steamworks
    REQUIRED_VARS _STEAMWORKS_INCLUDE_DIR _STEAMWORKS_LIBRARY
    VERSION_VAR Steamworks_VERSION
)

# ------------------------------------------------------------
# Export variables
# ------------------------------------------------------------

if(Steamworks_FOUND)
    set(Steamworks_INCLUDE_DIRS "${_STEAMWORKS_INCLUDE_DIR}")
    set(Steamworks_LIBRARIES "${_STEAMWORKS_LIBRARY}")

    if(WIN32)
        set(Steamworks_RUNTIME_DLL "${_STEAMWORKS_RUNTIME_DLL}")
    endif()

    if(NOT TARGET Steamworks::Steamworks)
        add_library(Steamworks::Steamworks INTERFACE IMPORTED)

        set_target_properties(Steamworks::Steamworks PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${Steamworks_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES "${Steamworks_LIBRARIES}"
        )
    endif()
endif()