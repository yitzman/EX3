cmake_minimum_required(VERSION 3.15)
project(EX3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(EX3
        main.cpp
        Interpreter
        Lexer.h
        Lexer.cpp
        Interpreter/Interpreter.cpp
        Interpreter/Interpreter.h
        Interpreter/Expression.cpp
        Interpreter/Expression.h
        Interpreter/Div.cpp
        Interpreter/Div.h
        Interpreter/BinaryOperator.cpp
        Interpreter/BinaryOperator.h
        Interpreter/Minus.cpp
        Interpreter/Minus.h
        Interpreter/Plus.cpp
        Interpreter/Plus.h
        Interpreter/Mul.cpp
        Interpreter/Mul.h
        Interpreter/Minus.h
        Interpreter/UMinus.cpp
        Interpreter/UMinus.h
        Interpreter/UnaryOperator.cpp
        Interpreter/UnaryOperator.h
        Interpreter/UPlus.cpp
        Interpreter/UPlus.h
        Interpreter/Value.cpp
        Interpreter/Value.h
        Interpreter/Variable.cpp
        Interpreter/Variable.h
        tester5
        )


