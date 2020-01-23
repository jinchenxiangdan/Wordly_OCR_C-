cmake_minimum_required(VERSION 3.15)
project(wordly_ocr)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 14)

add_executable(wordly_ocr  CharImgDatabase.cpp base64.h base64.cpp)

target_link_libraries(wordly_ocr LINK_PUBLIC sqlite3 ${OpenCV_LIBS})