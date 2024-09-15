cmake_minimum_required(VERSION 3.25)

project(application LANGUAGES CXX)

libhal_build_demos(
    DEMOS
    mpu6050_demo

    SOURCES
    src/mpu6050.cpp
    platforms/micromod.cpp
)