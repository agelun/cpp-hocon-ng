cmake_minimum_required(VERSION 3.2.2)

project(cpp-hocon VERSION 0.2.2)

string(MAKE_C_IDENTIFIER ${PROJECT_NAME} PROJECT_C_NAME)
string(TOUPPER ${PROJECT_C_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_C_NAME} PROJECT_NAME_LOWER)

# Common cmake setup
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Defaulting to a release build.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

list(APPEND BOOST_COMPONENTS thread date_time chrono filesystem system program_options)

# Add other dependencies
find_package(Boost 1.54 REQUIRED COMPONENTS ${BOOST_COMPONENTS})

# pthreads if you require the Boost.Thread component.
find_package(Threads)

# Display a summary of the features
include(FeatureSummary)
feature_summary(WHAT ALL)

add_subdirectory(lib)