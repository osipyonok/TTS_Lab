cmake_minimum_required(VERSION 3.13.0)

project(TextToSpeechLab LANGUAGES CXX)

if(MSVC)
    set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo" CACHE STRING 
        "Semicolon separated list of supported configuration types, only supports ${CMAKE_CONFIGURATION_TYPES} anything else will be ignored." FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()    
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS 
    Core 
    Gui
    Multimedia
    Widgets
)

file(GLOB_RECURSE Headers   "TTS_Lab/*.h")
source_group("Header files" FILES ${Headers})

file(GLOB_RECURSE Sources   "TTS_Lab/*.cpp")
source_group("Source files" FILES ${Sources})

file(GLOB_RECURSE Forms   "TTS_Lab/*.ui")
source_group("Forms" FILES ${Forms})

file(GLOB_RECURSE QrcFiles "TTS_Lab/*.qrc")
qt5_add_resources(Resources ${QrcFiles})
source_group("Resources" FILES ${Resources})

add_executable(TextToSpeechLab ${Headers} ${Sources} ${Forms} ${Resources})
set_target_properties(TextToSpeechLab PROPERTIES OUTPUT_NAME "TextToSpeechLab")

target_link_libraries(TextToSpeechLab
    Qt5::Core
    Qt5::Gui
    Qt5::Multimedia
    Qt5::Widgets
)

target_include_directories(TextToSpeechLab PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/TTS_Lab"
    "${CMAKE_CURRENT_BINARY_DIR}"
)
