//
// Created by kougianosg on 27-Aug-18.
//


#include <iostream>

#include <seqan/align.h>

using namespace seqan;


int main() {

    typedef String<char> TSequence;
    typedef StringSet<TSequence> TStringSet;  // actually stores the sequences
    typedef StringSet<TSequence, Dependent<> > TDepStringSet;  //  internally used by the AlignmentGraph
    typedef Graph<Alignment<TDepStringSet> > TAlignGraph;  // stores refs (does not copy sequences to it's structure!)
    typedef typename VertexDescriptor<TAlignGraph>::Type TVertexDescriptor;


    // Initializing the sequences and the string set.
    TSequence seq1 = "GARFIELDTHECAT";
    TSequence seq2 = "GARFIELDTHEBIGCAT";
    TSequence seq3 = "THEBIGCAT";

    TStringSet strings;
    appendValue(strings, seq1);
    appendValue(strings, seq2);
    appendValue(strings, seq3);

    // Load the string set into the Alignment Graph.
    TAlignGraph alignG(strings);
    TVertexDescriptor u,v;

    // Add two vertices covering "GARFIELD" in the first and the second sequence and connect them with an edge.
    u = addVertex(alignG, 0, 0, 8);
    v = addVertex(alignG, 1, 0, 8);
    addEdge(alignG, u, v);

    // Add two vertices covering "THE" in the first and the second sequence and connect them with an edge.
    u = addVertex(alignG, 0, 8, 3);
    v = addVertex(alignG, 1, 8, 3);
    addEdge(alignG, u, v);

    // Find the vertex covering "THE" in the first sequence and add the vertex covering "THE" in the third sequence and connect them with an edge.
    u = findVertex(alignG, 0, 8);
    v = addVertex(alignG, 2, 0, 3);
    addEdge(alignG, u, v);

    // Find the vertices covering "THE" in the second and the third sequence and connect them with an edge.
    u = findVertex(alignG, 1, 8);
    v = findVertex(alignG, 2, 0);
    addEdge(alignG, u, v);

    // Add two vertices covering "BIG" in the second and the third sequence and connect them with an edge.
    u = addVertex(alignG, 1, 11, 3);
    v = addVertex(alignG, 2, 3, 3);
    addEdge(alignG, u, v);

    // Add two vertices covering "CAT" in the first and the second sequence and connect them with an edge.
    u = addVertex(alignG ,0, 11, 3);
    v = addVertex(alignG, 1, 14, 3);
    addEdge(alignG, u, v);

    // Find the vertex covering "CAT" in the first sequence and add the vertex covering "CAT" in the third sequence and connect them with an edge.
    u = findVertex(alignG, 0, 11);
    v = addVertex(alignG, 2, 6, 3);
    addEdge(alignG, u, v);

    // Find the vertices covering "CAT" in the second and the third sequence and connect them with an edge.
    u = findVertex(alignG, 1, 14);
    v = findVertex(alignG, 2, 6);
    addEdge(alignG, u, v);

    std::cout << alignG << std::endl;

    return 0;
};