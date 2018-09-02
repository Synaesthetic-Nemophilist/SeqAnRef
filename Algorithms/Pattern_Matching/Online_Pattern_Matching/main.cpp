//
// Created by Jerry Kougianos on 02/09/2018.
//

#include <iostream>
#include <seqan/find.h>

using namespace seqan;


void exactMultiSeq();

void approxMyers();


int main() {

    std::cout << "Exact Matching\n";
    exactMultiSeq();

    std::cout << "\n Approximate Matching\n";
    approxMyers();

    return 0;
}


/**
 * Exact pattern match using WuManber for multi sequence set needle
 */
void exactMultiSeq() {

    // init haystack and needle
    CharString haystack = "Simon, send more money!";
    String<CharString> needles;
    appendValue(needles, "mo");
    appendValue(needles, "send");
    appendValue(needles, "more");

    // init Finder and Pattern instances
    Finder<CharString> finder(haystack);
    Pattern<String<CharString>, WuManber> pattern(needles);

    // run WuManber algo
    while(find(finder, pattern))
    {
        std::cout << '[' << beginPosition(finder) << ',' << endPosition(finder) << ")\t";
        std::cout << position(pattern) << '\t' << infix(finder) << std::endl;
    }

}

/**
 * Approx pattern match using Myer's algorithm with error tolerance of 2
 * NOTE: Myer's algorithm uses  is only applicable
 * to edit distance searches it cannot be specialized
 * or initialized with a scoring scheme.
 * In SeqAn, edit distance corresponds to the scoring scheme (0,-1,-1) (match, mismatch, gap)
 */
void approxMyers() {

    CharString haystack = "Simon, send more money!";
    CharString needle = "more";

    Finder<CharString> finder(haystack);
    Pattern<CharString, Myers<> > pattern(needle);
    while (find(finder, pattern, -2))
        while (findBegin(finder, pattern, getScore(pattern)))
            std::cout << '[' << beginPosition(finder) << ',' << endPosition(finder) << ")\t" << infix(finder) << std::endl;

}