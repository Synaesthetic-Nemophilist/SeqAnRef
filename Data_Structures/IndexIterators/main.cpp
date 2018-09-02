//
// Created by kougianosg on 16-Jul-18.
//

#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/stream.h>
#include <seqan/index.h>
#include <seqan/align.h>

using namespace seqan;


int findPattern();

template<typename TIndexSpec>
int preOrderDfs(CharString);

template<typename TIndexSpec>
void constrainedDfs(CharString, int);

void postOrderDfs(StringSet<CharString>);

void findMums(StringSet<CharString>);

void nodeDepth(String<char>);


int main() {

    int res = 0;

//     res = findPattern();

//    res = preOrderDfs<IndexEsa<>>("mississippi");
//    res = preOrderDfs<IndexWotd<>>("mississippi");

//    constrainedDfs<IndexEsa<>>("mississippi", 3);
//    constrainedDfs<IndexWotd<>>("mississippi", 3);

//    StringSet<CharString> myStringSet;
//    appendValue(myStringSet, "tobeornottobe");
//    appendValue(myStringSet, "thebeeonthecomb");
//    appendValue(myStringSet, "beingjohnmalkovich");
//    postOrderDfs(myStringSet);

//    StringSet<CharString> mumStringSet;
//    appendValue(mumStringSet, "CDFGHC");
//    appendValue(mumStringSet, "CDEFGAHC");
//    findMums(mumStringSet);

    String<char> myString = "abracadabra";
    nodeDepth(myString);



    return res;
}


/**
 * Finds pos of pattern in a CharString, via index->suffix tree traversal
 * @return
 */
int findPattern() {
    typedef Index<CharString> TIndex;
    TIndex index("How Much Wood Would A Woodchuck Chuck If A Woodchuck Could Chuck Wood?");

    Iterator<TIndex, TopDown<> >::Type it(index);

    CharString pattern = "Wood";

    while (repLength(it) < length(pattern)) {
        // go down edge starting with the next pattern char
        if (!goDown(it, pattern[repLength(it)]))
            return 0;

        unsigned endPos = std::min((unsigned) repLength(it), (unsigned) length(pattern));

        // compare remaining edge chars with pattern
        std::cout << representative(it) << std::endl;
        if (infix(representative(it), parentRepLength(it) + 1, endPos) !=
            infix(pattern, parentRepLength(it) + 1, endPos))
            return 0;
    }

    // if we reach here, the pattern was found
    // output match positions
    for (unsigned i = 0; i < length(getOccurrences(it)); ++i)
        std::cout << getOccurrences(it)[i] << std::endl;
}


/**
 * Pre-order depth first search of a suffix tree, using a generic index spec
 * @tparam TIndexSpec
 * @param str
 * @return
 */
template<typename TIndexSpec>
int preOrderDfs(CharString str) {

    typedef Index<CharString, TIndexSpec> TIndex;
    TIndex index(str);
    Iterator<TIndex, TopDown<ParentLinks<> > >::Type it(index);  // tag ParentLinks enables goUp()

    do {
        std::cout << representative(it) << std::endl;
        if (!goDown(it) && !goRight(it))
            while (goUp(it) && !goRight(it));  // go up until next sibling is traversable
    } while (!isRoot(it));

    return 0;
}


/**
 * Skip descent if next node has repLength(it) > threshold
 * @tparam TIndexSpec
 * @param str
 * @param threshold
 * @return
 */
template<typename TIndexSpec>
void constrainedDfs(CharString str, int threshold) {

    typedef Index<CharString, TIndexSpec> TIndex;
    TIndex index(str);
    Iterator<TIndex, TopDown<ParentLinks<> > >::Type it(index);

    do {
        std::cout << representative(it) << std::endl;
        if (!goDown(it) || repLength(it) > threshold)
            do {
                if (!goRight(it))
                    while (goUp(it) && !goRight(it));
            } while (repLength(it) > threshold);
    } while (!isRoot(it));
    std::cout << std::endl;
}

/**
 * Post-order depth first search of a suffix tree
 * @param set
 */
void postOrderDfs(StringSet<CharString> set) {

    typedef Index<StringSet<CharString> > TMyIndex;
    TMyIndex myIndex(set);

    Iterator<TMyIndex, TopDown<ParentLinks<Postorder> > >::Type myIterator(myIndex);

    // Top-down iterators start in the root node which is not the first node of a
    // post-order DFS. Thus we have to manually go to the DFS start with goBegin
    // alternatively we could use BottomUp spec iterator, which automatically starts
    // from the bottom and there is no need for goBegin(it)
    goBegin(myIterator);
    while(!atEnd(myIterator)) {
        std::cout << representative(myIterator) << std::endl;
        ++myIterator;
    }
}


/**
 * Prints to cout the maximal unique matches of a StringSet<CharString> set
 * @param set
 */
void findMums(StringSet<CharString> set) {

    typedef Index<StringSet<CharString> > TMyIndex;
    TMyIndex myIndex(set);

    Iterator<TMyIndex, Mums>::Type myMumsIterator(myIndex);
    while (!atEnd(myMumsIterator)) {
        std::cout << representative(myMumsIterator) << std::endl;
        ++myMumsIterator;
    }
}


/**
 * Couts the node's depth of a suffix tree using property maps
 * @param myString
 */
void nodeDepth(String<char> myString) {

    typedef Index<String<char>, IndexWotd<> > TMyIndex;
    TMyIndex myIndex(myString);
    String<int> propMap;

    Iterator<TMyIndex, TopDown<ParentLinks<Preorder> > >::Type myIterator(myIndex);

    int depth;
    while (!atEnd(myIterator))
    {
        if(isRoot(myIterator))
            depth = 0;
        else
            depth = getProperty(propMap, nodeUp(myIterator)) + 1;

        resizeVertexMap(propMap, myIndex);
        assignProperty(propMap, value(myIterator), depth);

        ++myIterator;
    }

    goBegin(myIterator);
    while (!atEnd(myIterator))
    {
        std::cout << getProperty(propMap, value(myIterator)) << '\t' << representative(myIterator) << std::endl;
        ++myIterator;
    }
}