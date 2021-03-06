project(SAR)

cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11 /MP /Wall")
endif()

set(SAR_SOURCES
    build/driver.cpp
    src/Environment/Environment.cpp
    src/GeneticAlgorithm/Utilities/GeneticAlgorithmUtilities
    src/GeneticAlgorithm/GeneticAlgorithmBool.cpp
)

set(SAR_HEADERS
    include/Environment/Environment.hpp
    include/Environment/Support/Coord.hpp
    include/Environment/Support/EnvironmentTypes/AreaType.hpp
    include/Environment/Support/EnvironmentTypes/TerrainType.hpp
    include/Environment/Support/Tiles/Empty.hpp
    include/Environment/Support/Tiles/Falsepos.hpp
    include/Environment/Support/Tiles/Target.hpp
    include/Environment/Support/Tiles/Tile.hpp
    include/GeneticAlgorithm/GeneticAlgorithm_NeuralNetwork.hpp
    include/GeneticAlgorithm/Utilities/GeneticAlgorithmUtilities.hpp
    include/GeneticProgrammer/GeneticProgrammer_NeuralNetwork.hpp
    include/GeneticProgrammer/implementation/GeneticProgrammer_NeuralNetwork.imp
    include/NeuralNetwork/Neuron.hpp
    include/NeuralNetwork/NeuralNetwork.hpp
    include/NeuralNetwork/NeuralNetworkController.hpp
    include/NeuralNetwork/NeuralNetworkFactory.hpp
    include/NeuralNetwork/implementation/NeuralNetworkController.imp
    include/NeuralNetwork/implementation/NeuralNetworkFactory.imp
    include/NeuralNetwork/implementation/NeuralNetwork.imp
    include/NeuralNetwork/implementation/Neuron.imp
    include/Simulation/SARsimulation.hpp
    include/Simulation/implementation/SARsimulation.imp
    include/Simulation/SearchAgents/SearchAgents.hpp
    include/Simulation/SearchAgents/SearchAgentsType/Drone.hpp
    include/Simulation/SearchAgents/SearchAgentsType/implementation/Drone.imp
    include/Simulation/SearchAgents/SearchAgentsType/SearchAgentsTypes.hpp
)

include_directories(include)

add_executable(${PROJECT_NAME}
    ${SAR_HEADERS}
    ${SAR_SOURCES}
)

set(SAR_DATA

)

foreach(DATA ${SAR_DATA})
    configure_file(${DATA} ${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILENAME} COPYONLY)
endforeach()