add_executable(app app.cpp
)

target_link_libraries(app PRIVATE no_name_engine)
target_include_directories(app PRIVATE ${PROJECT_SOURCE_DIR}/no_name_engine)