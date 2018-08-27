//
// Created by Jerry Kougianos on 27/08/2018.
//

#include <iostream>
#include <seqan/sequence.h>
#include <seqan/stream.h>
#include <seqan/store.h>

using namespace seqan;

int main() {

//    CharString fileName = getAbsolutePath();
    GffFileIn file(toCString("/Users/nomaterials/CLionProjects/SeqAnRef/Store/GenomeAnnotations/data/assignment_annotations.gtf"));

    FragmentStore<> store;
    readRecords(store, file);

    // Create AnnotationTree iterator
    Iterator<FragmentStore<>, AnnotationTree<> >::Type it;
    it = begin(store, AnnotationTree<>());

    std::cout << "Number of children for each mRNA: " << std::endl;
    unsigned count = 0;
    // Go down to the first leaf (first child of the first mRNA)
    while(goDown(it))
    {}

    while (!atEnd(it))
    {
        ++count;
        // Iterate over all siblings and count
        while (goRight(it))
            ++count;
        std::cout << count << std::endl;
        count = 0;
        // Jump to the next mRNA or gene, go down to its first leaf and count it
        if (!atEnd(it))
        {
            goNext(it);
            if (!atEnd(it))
                while (goDown(it))
                {}
        }
    }
    return 0;
}