#third party packages

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

#files

file(GLOB EssexEngineGTK3Driver_HEADERS
    "src/Drivers/GTK3Driver/*.h"
)
file(GLOB EssexEngineGTK3Driver_SRC
    ${EssexEngineGTK3Driver_HEADERS}
    "src/Drivers/GTK3Driver/*.cpp"
)

#setup headers

file(COPY ${EssexEngineGTK3Driver_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineGTK3Driver/")

#setup build

add_library(EssexEngineGTK3Driver SHARED ${EssexEngineGTK3Driver_SRC})
target_link_libraries(EssexEngineGTK3Driver EssexEngineCore)
target_link_libraries(EssexEngineGTK3Driver EssexEngineWindowDaemon)
target_link_libraries(EssexEngineGTK3Driver ${GTK3_LIBRARIES})
