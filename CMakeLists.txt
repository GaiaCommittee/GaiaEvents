#==============================
# Requirements
#==============================

cmake_minimum_required(VERSION 3.10)

#==============================
# Project Settings
#==============================

if (NOT PROJECT_DECLARED)
    project("Gaia Events" LANGUAGES CXX VERSION 1.0)
    set(PROJECT_DECLARED)
endif()

#==============================
# Project Modules
#==============================

add_subdirectory("GaiaEvents")

if (WITH_TEST)
    add_subdirectory("GaiaEventsTest")
endif()