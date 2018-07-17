//
// Created by kougianosg on 17-Jul-18.
//

#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/stream.h>
#include <seqan/align.h>

using namespace seqan;


void constructAlignment();

void globalAlignSimpleScore();

void globalAlignBlosum62();

void globalAlignBlosum62AffineDynamic();



int main() {

    std::cout << "Construction of alignment" << std::endl;
    constructAlignment();
    std::cout << "Global Align - Simple Score" << std::endl;
    globalAlignSimpleScore();
    std::cout << "Global Align - Blosum62" << std::endl;
    globalAlignBlosum62();
    std::cout << "Global Align - Blosum62 - Affine & Dynamic Gap model" << std::endl;
    globalAlignBlosum62AffineDynamic();

    return 0;
};


void constructAlignment() {

    typedef char TChar;                             // character type
    typedef String<TChar> TSequence;                // sequence type
    typedef Align<TSequence, ArrayGaps> TAlign;     // align type
    typedef Row<TAlign>::Type TRow;                 // gapped sequence type

    TSequence seq1 = "CDFGDC";
    TSequence seq2 = "CDEFGAHGC";

    TAlign align;
    resize(rows(align), 2);
    assignSource(row(align, 0), seq1);
    assignSource(row(align, 1), seq2);
    std::cout << "Cropped alignment: " << std::endl;
    std::cout << align;

    std::cout << "Gapped alignment: " << std::endl;
    TRow & row1 = row(align, 0);  // important: we use refs of the rows, in order for changes to take effect
    TRow & row2 = row(align, 1);
    insertGap(row1, 2);
    std::cout << align;
    insertGaps(row1, 5, 2);
    std::cout << align;


    std::cout << std::endl << "ViewToSource1: " << std::endl;
    for (auto c: row1)
        std::cout << c << " ";
    std::cout << std::endl;

    for (unsigned i = 0; i < length(row1); ++i)
        std::cout << toSourcePosition(row1, i) << " ";
    std::cout << std::endl;


    std::cout << std::endl << "ViewToSource2: " << std::endl;
    for (auto c: row2)
        std::cout << c << " ";
    std::cout << std::endl;

    for (unsigned i = 0; i < length(row2); ++i)
        std::cout << toSourcePosition(row2, i) << " ";
    std::cout << std::endl;


    std::cout << std::endl << "SourceToView1: " << std::endl;
    for (auto c: source(row1))
        std::cout << c << " ";
    std::cout << std::endl;

    for (unsigned i = 0; i < length(source(row1)); ++i)
        std::cout << toViewPosition(row1, i) << " ";
    std::cout << std::endl;


    std::cout << std::endl << "SourceToView2: " << std::endl;
    for (auto c: source(row2))
        std::cout << c << " ";
    std::cout << std::endl;

    for (unsigned i = 0; i < length(source(row2)); ++i)
        std::cout << toViewPosition(row2, i) << " ";
    std::cout << std::endl;
}


/**
 * Global alignment using Simple scoring scheme
 */
void globalAlignSimpleScore() {

    typedef String<AminoAcid> TSequence;
    typedef Align<TSequence, ArrayGaps> TAlign;

    TSequence seq1 = "TELKDD";
    TSequence seq2 = "LKTEL";
    int match = -0;
    int mismatch = -1;
    int gap = -1;

    TAlign align;
    resize(rows(align), 2);
    assignSource(row(align, 0), seq1);
    assignSource(row(align, 1), seq2);

    int score = globalAlignment(align, Score<int, Simple>(match, mismatch, gap));
    std::cout << "Score: " << score << std::endl;
    std::cout << align << std::endl;
}

/**
 * Global alignment using Blosum62 scoring scheme
 */
void globalAlignBlosum62() {

    typedef String<AminoAcid> TSequence;
    typedef Align<TSequence, ArrayGaps> TAlign;

    TSequence seq1 = "TELKDD";
    TSequence seq2 = "LKTEL";

    int gap = -1;

    TAlign align;
    resize(rows(align), 2);
    assignSource(row(align, 0), seq1);
    assignSource(row(align, 1), seq2);

    int score = globalAlignment(align, seqan::Blosum62(gap, gap));
    std::cout << "Score: " << score << std::endl;
    std::cout << align << std::endl;

}

/**
 * Global alignment using Blosum62 scoring scheme
 * and Affine Gap model first, then Dynamic Gap model
 */
void globalAlignBlosum62AffineDynamic() {
    typedef String<AminoAcid> TSequence;
    typedef Align<TSequence, ArrayGaps> TAlign;

    TSequence seq1 = "TELKDD";
    TSequence seq2 = "LKTEL";

    int gapOpen = -10;
    int gapExtend = -2;

    TAlign alignAffine;
    resize(rows(alignAffine), 2);
    assignSource(row(alignAffine, 0), seq1);
    assignSource(row(alignAffine, 1), seq2);

    TAlign alignDynamic;
    resize(rows(alignDynamic), 2);
    assignSource(row(alignDynamic, 0), seq1);
    assignSource(row(alignDynamic, 1), seq2);

    int scoreAffine = globalAlignment(alignAffine, Blosum62(gapExtend, gapOpen), AffineGaps());
    std::cout << "ScoreAffine: " << scoreAffine << std::endl;
    std::cout << alignAffine << std::endl;

    int scoreDynamic = globalAlignment(alignDynamic, Blosum62(gapExtend, gapOpen), DynamicGaps());
    std::cout << "ScoreDynamic: " << scoreDynamic << std::endl;
    std::cout << alignDynamic << std::endl;

}