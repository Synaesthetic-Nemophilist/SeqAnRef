//
// Created by kougianosg on 31-Aug-18.
//

#include <seqan/stream.h>
#include <seqan/sequence_journaled.h>
#include <seqan/journaled_string_tree.h>

using namespace seqan;

void JournaledStringBasics();
void JST();


// Custom functor for printing upon seq match on JST
template <typename TTraverser>
struct MatchPrinter
{
    TTraverser & trav;

    MatchPrinter(TTraverser & _trav) : trav(_trav)
    {}

    void
    operator()()
    {
        auto pos = position(trav);
        for (auto p : pos)
        {
            std::cout  << "Seq: " << p.i1 << " Pos: " << p.i2 << std::endl;
        }
    }
};



int main(){

    // JournaledString test
    JournaledStringBasics();

    std::cout << std::endl << "JST output" << std::endl;

    // Journaled String Tree test
    JST();


    return 0;
}



void JournaledStringBasics() {

    typedef String<char, Journaled<Alloc<>, SortedArray, Alloc<> > > TJournaledString;
    typedef Host<TJournaledString>::Type THost;

    THost hostStr = "thisisahostsequence";
    TJournaledString journalStr;
    setHost(journalStr, hostStr);

    std::cout << "After creating the Journaled String:" << std::endl;
    std::cout << "Host: " << host(journalStr) << std::endl;
    std::cout << "Journal: " << journalStr << std::endl;
    std::cout << "Nodes: " << journalStr._journalEntries << std::endl;
    std::cout << std::endl;


    insert(journalStr, 7, "modified");
    erase(journalStr, 19, 27);

    std::cout << "After modifying the Journaled String:" << std::endl;
    std::cout << "Host: " << host(journalStr) << std::endl;
    std::cout << "Journal: " << journalStr << std::endl;
    std::cout << "Nodes: " << journalStr._journalEntries << std::endl;
    std::cout << std::endl;

    flatten(journalStr);
    std::cout << "After flatten the Journaled String:" << std::endl;
    std::cout << "Host: " << host(journalStr) << std::endl;
    std::cout << "Journal: " << journalStr << std::endl;
    std::cout << "Nodes: " << journalStr._journalEntries << std::endl;

}


void JST() {

    typedef JournaledStringTree<DnaString> TJst;
    typedef Pattern<DnaString, Horspool> TPattern;
    typedef Traverser<TJst>::Type TTraverser;

    // Init ref seq and JST
    DnaString seq = "AGATCGAGCGAGCTAGCGACTCAG";
    TJst jst(seq, 10);

    // Load data into JST
    insert(jst, 1, 3, std::vector<unsigned>{1, 3, 5, 6, 7}, DeltaTypeDel());
    insert(jst, 8, "CGTA", std::vector<unsigned>{1, 2}, DeltaTypeIns());
    insert(jst, 10, 'C', std::vector<unsigned>{4, 9}, DeltaTypeSnp());
    insert(jst, 15, 2, std::vector<unsigned>{0, 4, 7}, DeltaTypeDel());
    insert(jst, 20, 'A', std::vector<unsigned>{0, 9}, DeltaTypeSnp());
    insert(jst, 20, Pair<unsigned, DnaString>(1, "CTC"), std::vector<unsigned>{1, 2, 3, 7}, DeltaTypeSV());

    // Init needle pattern and tree traverser
    DnaString ndl = "AGCGT";
    TTraverser trav(jst, length(ndl));

    TPattern pat(ndl);
    JstExtension<TPattern> ext(pat);

    MatchPrinter<TTraverser> delegate(trav);
    find(trav, ext, delegate);

}

