# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_AUTOMOC TRUE)
# Define project name
project(AIDA)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

find_package(Qt5 COMPONENTS REQUIRED Quick Qml Core Gui Widgets TextToSpeech)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

link_directories(
    ${OpenCV_LIB_DIR}
)

# Declare the executable target built from your sources

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(project_sources mainwindow.cpp camera.cpp main.cpp)

set(project_headers camera.h)

set(project_ui mainwindow.ui)

qt5_add_resources(project_resources imageresources.qrc)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})
add_executable(AIDA 
	${project_sources} 
	${project_headers}
	${ui_wrap} 
	${moc_sources} ${project_resources})
    
target_link_libraries(AIDA 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
  ${OpenCV_LIBS})


# need this to include the auto generated ui_mainwindow.h 
# file from the qt5_wrap_ui call below.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
