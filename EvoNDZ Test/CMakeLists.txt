cmake_minimum_required(VERSION 3.14)

add_executable(EvoNDZ_Test "source/app.cpp")

target_link_libraries(EvoNDZ_Test 
                                EvoNDZ 
                                glad
                                ${THIRDPARTY_LIBS}
                     )