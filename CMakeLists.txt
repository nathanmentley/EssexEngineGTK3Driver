find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(Cairo)

link_directories(${GTK3_LIBRARY_DIRS})

ee_setup_project("EssexEngineGTK3Driver" "src/Drivers/GTK3Driver/")
target_link_libraries(EssexEngineGTK3Driver EssexEngineCore)
target_link_libraries(EssexEngineGTK3Driver EssexEngineWindowDaemon)
target_link_libraries(EssexEngineGTK3Driver ${GTK3_LIBRARIES})
target_link_libraries(EssexEngineGTK3Driver ${Cairo_LIBRARIES})

target_include_directories(EssexEngineGTK3Driver PRIVATE ${GTK3_INCLUDE_DIRS})
target_include_directories(EssexEngineGTK3Driver PRIVATE ${Cairo_INCLUDE_DIRS})
