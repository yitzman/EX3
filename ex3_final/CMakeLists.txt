cmake_minimum_required(VERSION 3.15)
project(mileStone1)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(mileStone1 main.cpp Command.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h DefineVarCommend.cpp DefineVarCommend.h ConnectCommand.cpp ConnectCommand.h Lexer.cpp Lexer.h Parser.cpp Parser.h BinaryOperator.cpp BinaryOperator.h Div.cpp Div.h Expression.cpp Expression.h Interpreter.cpp Interpreter.h Minus.cpp Minus.h Mul.cpp Mul.h Plus.cpp Plus.h UMinus.cpp UMinus.h UnaryOperator.cpp UnaryOperator.h UPlus.cpp UPlus.h Value.cpp Value.h Variable.cpp Variable.h)