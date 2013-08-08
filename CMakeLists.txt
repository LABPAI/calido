project(Calido)
cmake_minimum_required(VERSION 2.8.8)


#Turn on Automoc to automatically compile qt moc files
set(CMAKE_AUTOMOC ON)


#Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Compile with debug info
set(CMAKE_BUILD_TYPE Debug)

#Enable c++ 11
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

#Include all file types in project
file(GLOB UI_FILES *.ui)
file(GLOB HEADERS  *.h *.hxx)
file(GLOB SRCS     *.cpp *.cxx *.c)
file(GLOB RFILES   *qrc)


#Add qt to project
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Declarative REQUIRED )
find_package( Qt5Core REQUIRED )



set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")



#Compile qt designer files
qt5_wrap_ui(UI ${UI_FILES})

#Add resource files
qt5_add_resources(RESOURCES ${RFILES} )





#Create an executable
add_executable(Calido ${UI} ${HEADERS} ${SRCS} ${RESOURCES})


qt5_use_modules(Calido Widgets Declarative Core)
