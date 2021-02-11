cmake_minimum_required(VERSION 3.14.0)

set(vst3sdk_SOURCE_DIR {{cookiecutter.VST3_SDK_PATH}})
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project({{cookiecutter.CMAKE_PROJECT_NAME_CLI}})
  
set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin({{cookiecutter.CMAKE_PROJECT_NAME_CLI}}     
    source/version.h
    source/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}cids.h
    source/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}processor.h
    source/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}processor.cpp
    source/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}controller.h
    source/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}controller.cpp
    source/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}entry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
	target_sources({{cookiecutter.CMAKE_PROJECT_NAME_CLI}}
		PRIVATE
			resource/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}editor.uidesc
	)
    target_link_libraries({{cookiecutter.CMAKE_PROJECT_NAME_CLI}}
        PRIVATE
            vstgui_support
    )
    smtg_add_vst3_resource({{cookiecutter.CMAKE_PROJECT_NAME_CLI}} "resource/{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}editor.uidesc")
endif()
# -------------------

smtg_add_vst3_snapshot({{cookiecutter.CMAKE_PROJECT_NAME_CLI}} resource/64BEF73FD69953078C85A03290084365_snapshot.png)
smtg_add_vst3_snapshot({{cookiecutter.CMAKE_PROJECT_NAME_CLI}} resource/64BEF73FD69953078C85A03290084365_snapshot_2.0x.png)

target_link_libraries({{cookiecutter.CMAKE_PROJECT_NAME_CLI}}
    PRIVATE
        sdk
)

if(SMTG_MAC)
    smtg_set_bundle({{cookiecutter.CMAKE_PROJECT_NAME_CLI}} INFOPLIST 
        "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" 
        PREPROCESS
    )
elseif(SMTG_WIN)
    target_sources({{cookiecutter.CMAKE_PROJECT_NAME_CLI}} PRIVATE 
        resource/win32resource.rc
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT {{cookiecutter.CMAKE_PROJECT_NAME_CLI}})
	
	set_target_properties({{cookiecutter.CMAKE_PROJECT_NAME_CLI}} PROPERTIES
		VS_DEBUGGER_COMMAND
			"$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
		VS_DEBUGGER_COMMAND_ARGUMENTS
			" --pluginfolder \"$(OutDir)\" "
	)
endif()


