cmake_minimum_required(3.10)

find_path(GaiaEvents_INCLUDE_DIRS "GaiaEvents")
find_library(GaiaEvents_LIBS "GaiaEvents")

if (GaiaEvents_INCLUDE_DIRS AND GaiaEvents_LIBS)
    set(GaiaExceptions_FOUND TRUE)
endif()