# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)

# Name of project and that it is C++ only.
project (SeqAnTut CXX)

set(CMAKE_CXX_STANDARD 14)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Load the SeqAn module and fail if not found.
find_package (SeqAn REQUIRED)

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# Add executables and link against SeqAn dependencies.
add_executable(FirstExample first_example/main.cpp)
target_link_libraries (FirstExample ${SEQAN_LIBRARIES})

add_executable(ArgParser arg_parser/main.cpp)
target_link_libraries (ArgParser ${SEQAN_LIBRARIES})

add_executable(StringsSegments Data_Structures/strings_segments/main.cpp)
target_link_libraries (StringsSegments ${SEQAN_LIBRARIES})

add_executable (CommonQGramMatrix Data_Structures/CommonQGramMatrix/main.cpp)
target_link_libraries (CommonQGramMatrix ${SEQAN_LIBRARIES})

add_executable (IndexIterators Data_Structures/IndexIterators/main.cpp)
target_link_libraries (IndexIterators ${SEQAN_LIBRARIES})

add_executable (Alignment Data_Structures/Alignment/main.cpp)
target_link_libraries (Alignment ${SEQAN_LIBRARIES})

add_executable (GraphAlignment Data_Structures/Alignment/GraphAlignment/main.cpp)
target_link_libraries (GraphAlignment ${SEQAN_LIBRARIES})

add_executable(GenomeAnnotations Data_Structures/Store/GenomeAnnotations/main.cpp)
target_link_libraries (GenomeAnnotations ${SEQAN_LIBRARIES})

add_executable(GraphHMM Data_Structures/Graphs/HMM/main.cpp)
target_link_libraries (GraphHMM ${SEQAN_LIBRARIES})

add_executable(Modifiers Data_Structures/Modifiers/main.cpp)
target_link_libraries (Modifiers ${SEQAN_LIBRARIES})

add_executable(JournaledStringTree Data_Structures/JournaledStringTree/main.cpp)
target_link_libraries (JournaledStringTree ${SEQAN_LIBRARIES})

add_executable(Online_Pattern_Matching Algorithms/Pattern_Matching/Online_Pattern_Matching/main.cpp)
target_link_libraries (Online_Pattern_Matching ${SEQAN_LIBRARIES})

add_executable(Indexed_Pattern_Matching Algorithms/Pattern_Matching/Indexed_Pattern_Matching/main.cpp)
target_link_libraries (Indexed_Pattern_Matching ${SEQAN_LIBRARIES})

add_executable(Optimal_Search_Scheme Algorithms/Pattern_Matching/Optimal_Search_Scheme/main.cpp)
target_link_libraries (Optimal_Search_Scheme ${SEQAN_LIBRARIES})

add_executable(Global_Alignment Algorithms/DP_Alignment/Pairwise_Sequence_Alignment/Global_Alignment/main.cpp)
target_link_libraries (Global_Alignment ${SEQAN_LIBRARIES})

add_executable(Overlap_Alignment Algorithms/DP_Alignment/Pairwise_Sequence_Alignment/Overlap_Alignment/main.cpp)
target_link_libraries (Overlap_Alignment ${SEQAN_LIBRARIES})

add_executable(Specialized_Alignment Algorithms/DP_Alignment/Pairwise_Sequence_Alignment/Specialized_Alignment/main.cpp)
target_link_libraries (Specialized_Alignment ${SEQAN_LIBRARIES})



# Search for zlib as a dependency for SeqAn.
find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries(CommonQGramMatrix ${ZLIB_LIBRARIES} )
    target_link_libraries(IndexIterators ${ZLIB_LIBRARIES} )
    target_link_libraries(Alignment ${ZLIB_LIBRARIES})
endif( ZLIB_FOUND )









