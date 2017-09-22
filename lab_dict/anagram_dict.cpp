/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream wordsFile(filename);
    string word, alphaWord;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            alphaWord = word;
            std::sort(alphaWord.begin(), alphaWord.end());
            try {
                dict.at(alphaWord).push_back(word);
            } catch (std::out_of_range e) {
                dict.insert(make_pair(alphaWord, vector<string> {word}));
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    string alphaWord;
    for (string const & word : words) {
        alphaWord = word;
        std::sort(alphaWord.begin(), alphaWord.end());
        dict[alphaWord].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    string alphaWord = word;
    std::sort(alphaWord.begin(), alphaWord.end());
    auto lookup = dict.find(alphaWord);
    if(lookup != dict.end())
        return lookup->second;
    else
        return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> out;
    for (auto currAna : dict) {
        if(currAna.second.size() > 1)
            out.push_back(currAna.second);
    }
    return out;
}
