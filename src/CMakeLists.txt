# include ParadisEO-files and src/ directory
include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

# define library as target
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(QAP_SOURCES
		QAP.h
		QAPEval.h
		QAPInit.h
		QAPSwapNeighbor.h
		QAPSwapNeighborhood.h
		)

#add_library(lQAP STATIC ${QAP_SOURCES})

