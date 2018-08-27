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

add_executable(StringsSegments strings_segments/main.cpp)
target_link_libraries (StringsSegments ${SEQAN_LIBRARIES})

add_executable (CommonQGramMatrix CommonQGramMatrix/main.cpp)
target_link_libraries (CommonQGramMatrix ${SEQAN_LIBRARIES})

add_executable (IndexIterators IndexIterators/main.cpp)
target_link_libraries (IndexIterators ${SEQAN_LIBRARIES})

add_executable (Alignment Alignment/main.cpp)
target_link_libraries (Alignment ${SEQAN_LIBRARIES})



# Search for zlib as a dependency for SeqAn.
find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries( CommonQGramMatrix ${ZLIB_LIBRARIES} )
    target_link_libraries( IndexIterators ${ZLIB_LIBRARIES} )
    target_link_libraries(Alignment ${ZLIB_LIBRARIES})
endif( ZLIB_FOUND )