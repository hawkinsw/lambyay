PROJECT(Lambda)

cmake_minimum_required(VERSION 3.16)

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/lambdalexer.cpp)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
    OUTPUT ${FlexOutput}
    COMMAND ${FLEX_EXECUTABLE}
            --outfile=${FlexOutput}
            ${CMAKE_SOURCE_DIR}/lambda.l
    COMMENT "Generating lambdalexer.cpp"
    )
ENDIF()

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/lambdaparser.cpp)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
    OUTPUT ${BisonOutput}
    COMMAND ${BISON_EXECUTABLE}
    ARGS    --defines=${CMAKE_SOURCE_DIR}/lambdaparser.h
            -o ${BisonOutput}
            ${CMAKE_SOURCE_DIR}/lambda.y
    COMMENT "Generating lambdaparser.cpp"
    )
ENDIF()


add_executable(lambda ${FlexOutput} ${BisonOutput})
