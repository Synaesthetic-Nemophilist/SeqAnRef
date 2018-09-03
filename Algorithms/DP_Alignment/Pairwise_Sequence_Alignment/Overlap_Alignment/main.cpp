//
// Created by kougianosg on 03-Sep-18.
//

#include <iostream>
#include <seqan/align.h>

using namespace seqan;

int main() {
    typedef String<Dna> TSequence;                              // sequence type
    typedef StringSet<TSequence> TStringSet;                    // container for strings
    typedef StringSet<TSequence, Dependent<> > TDepStringSet;   // dependent string set
    typedef Graph<Alignment<TDepStringSet> > TAlignGraph;       // alignment graph

    TSequence seq1 = "AAATGACGGATTG";
    TSequence seq2 = "TGGGA";

    TStringSet sequences;
    appendValue(sequences, seq1);
    appendValue(sequences, seq2);

    TAlignGraph alignG(sequences);


    // In this example we put the shorter sequence on the vertical axis of our alignment matrix.
    // Hence, we have to use free end-gaps in the first and last row, which corresponds to the
    // first and the last parameter in the AlignConfig object
    int score = globalAlignment(alignG, Score<int, Simple>(1, -1, -1), AlignConfig<true, false, false, true>());
    std::cout << "Score: " << score << std::endl;
    std::cout << alignG << std::endl;

    return 0;
}