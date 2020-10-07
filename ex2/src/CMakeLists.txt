set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCE_FILES
        Utils/BinaryUtil.h
        Utils/BinaryUtil.cpp
        OperationMode/ECBOperationMode.cpp
        OperationMode/ECBOperationMode.h
        OperationMode/CTROperationMode.cpp
        OperationMode/CTROperationMode.h
        OperationMode/CFBOperationMode.cpp
        OperationMode/CFBOperationMode.h
        OperationMode/OFBOperationMode.cpp
        OperationMode/OFBOperationMode.h
        OperationMode/Base/OperationModeBase.cpp
        OperationMode/Base/OperationModeBase.h
        OperationMode/CBCOperationMode.cpp
        OperationMode/CBCOperationMode.h
        main.cpp)


add_executable(ex2  ${SOURCE_FILES})
add_library(${BINARY}_lib STATIC ${SOURCE_FILES})