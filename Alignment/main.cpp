//
// Created by kougianosg on 17-Jul-18.
//

#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/stream.h>
#include <seqan/align.h>

using namespace seqan;


void globalAlignSimpleScore();

void globalAlignBlosum62();

void globalAlignBlosum62AffineDynamic();



int main() {

    std::cout << "Global Align - Simple Score" << std::endl;
    globalAlignSimpleScore();
    std::cout << "Global Align - Blosum62" << std::endl;
    globalAlignBlosum62();
    std::cout << "Global Align - Blosum62 - Affine & Dynamic Gap model" << std::endl;
    globalAlignBlosum62AffineDynamic();

    return 0;
};


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