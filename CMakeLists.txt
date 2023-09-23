cmake_minimum_required(VERSION 3.25.1)
project(Chroma VERSION 1.0.0)


set(JUCE_DIR "${CMAKE_BINARY_DIR}/dependencies/JUCE")
set(Q_DIR "${CMAKE_BINARY_DIR}/dependencies/q")
set(INFRA_DIR "${CMAKE_BINARY_DIR}/dependencies/infra")


# Install JUCE framework

if(NOT EXISTS ${JUCE_DIR})
    execute_process(
        COMMAND git clone https://github.com/juce-framework/JUCE.git ${JUCE_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )

    if(result)
        message(FATAL_ERROR "Failed to clone JUCE: ${output}")
    endif()
endif()


# Install q

if(NOT EXISTS ${Q_DIR})
    execute_process(
        COMMAND git clone https://github.com/chromaaudio/q.git ${Q_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )

    if(result)
        message(FATAL_ERROR "Failed to clone q: ${output}")
    endif()
endif()


# Install infra

if(NOT EXISTS ${INFRA_DIR})
    execute_process(
        COMMAND git clone https://github.com/chromaaudio/infra.git ${INFRA_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )

    if(result)
        message(FATAL_ERROR "Failed to clone infra: ${output}")
    endif()
endif()


add_subdirectory(${JUCE_DIR})

include_directories("${INFRA_DIR}/include/")
include_directories("${Q_DIR}/q_lib/include/")
include_directories("chromalib/include")

add_subdirectory(ChromaPitch)
add_subdirectory(ChromaScope)
