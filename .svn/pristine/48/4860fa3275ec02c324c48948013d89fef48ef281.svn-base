/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    Dict<string, int> hash(1000);
    while (infile.good()) {
        string word = infile.getNextWord();
        hash[word]++;
    }
    vector<pair<string, int>> ret;
    for (auto it : hash) {
        if(it.second >= threshold)
            ret.push_back(it);
    }
    return ret;

}
