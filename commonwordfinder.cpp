/*******************************************************************************
 * Name          : cwf.cpp
 * Author        : Andrew Chen
 * Date          : 5/1/17
 * Description   : Finds the most commonly used words in the input file
 ******************************************************************************/

#include "rbtree.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

bool compare_pairs(pair<string, int> p1,
                   pair<string, int> p2) {
    return p1.second > p2.second;
}

int numDigit(int num) {
    int digits = 0;
    while (num) {
        num /= 10;
        digits++;
    }
    return digits;
}

template <typename K, typename V>
string inorder_traversal(Tree *tree) {
    RedBlackTree<K, V> *rbt = static_cast<RedBlackTree<K, V> *>(tree);
    ostringstream oss;
    oss << "[";
    typename RedBlackTree<K, V>::iterator it = rbt->begin();
    while (it != rbt->end()) {
        if (it != rbt->begin()) {
            oss << ", ";
        }
        oss << (*it).first;
        ++it;
    }
    oss << "]";
    return oss.str();
}

template <typename K, typename V>
void test_find(Tree *tree) {
    RedBlackTree<K, V> *rbt = static_cast<RedBlackTree<K, V> *>(tree);
    typename RedBlackTree<K, V>::iterator it = rbt->begin();
    while (it != rbt->end()) {
        K key = (*it).first;
        if (rbt->find(key) == rbt->end()) {
            ostringstream oss;
            oss << "Cannot find key '" << key << "' in tree.";
            throw tree_exception(oss.str());
        }
        ++it;
    }
}

//template <typename K, typename V>
void display_stats(Tree *tree, vector< pair<string, int> > vec, int limit) {
    cout << "Total unique words: " << vec.size() << endl;
    int longest_word = vec[0].first.length();
    int longest_num = numDigit(vec[0].second);
    
    if ((unsigned) limit > vec.size()) {
        for (size_t j = 0; j < vec.size(); ++j) {
            if (vec[j].first.length() > (unsigned) longest_word) {
                longest_word = vec[j].first.length();
            }
            if (numDigit(vec[j].second) > longest_num) {
                longest_num = numDigit(vec[j].second);
            }
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i == vec.size()-1) {
                cout << right << setw(numDigit(vec.size())) << i+1 << right << setw(1) << ". ";
                cout << left << setw(longest_word+1) << vec[i].first;
                cout << left << vec[i].second;
            }
            else {
                cout << right << setw(numDigit(vec.size())) << i+1 << right << setw(1) <<  ". ";
                cout << left << setw(longest_word+1) << vec[i].first;
                cout << left << vec[i].second << endl;
            }
        }
    }
    else {
        for (int j = 0; j < limit; ++j) {
            if (vec[j].first.length() > (unsigned) longest_word) {
                longest_word = vec[j].first.length();
            }
            if (numDigit(vec[j].second) > longest_num) {
                longest_num = numDigit(vec[j].second);
            }
        }
        for (int i = 0; i < limit; ++i) {
            if (i == limit-1) {
                cout << right << setw(numDigit(limit)) << i+1 << right << setw(1) <<  ". ";
                cout << left << setw(longest_word+1) << vec[i].first;
                cout << left << vec[i].second;
            }
            else{
                cout << right << setw(numDigit(limit)) << i+1 << right << setw(1) << ". ";
                cout << left << setw(longest_word+1) << vec[i].first;
                cout << left << vec[i].second << endl;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./commonwordfinder <filename> [limit]" << endl;
        return 1;
    }
    istringstream iss;
    int limit = 10;
    if (argc == 3) {
        int num;
        iss.str(argv[2]);
        if (!(iss >> num) || num < 0) {
            cerr << "Error: Invalid limit '" << argv[2] << "' received." << endl;
            return 1;
        }
        else {
            limit = num;
        }
    }
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error: Cannot open file '" << argv[1] << "' for input." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    char c;
    string word;
    RedBlackTree<string, int> *rbt = new RedBlackTree<string, int>();

    try {
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (input_file.get(c)) {
            // Check for Unacceptable symbols: NOT(letters, single quote, hypens)
            if ((c >= 97 && c <= 122) || c == 45 || c == 39) {
                // accceptable characters
                word += c;
            }
            else if (c >= 65 && c <= 90) {
                // Upper case letters. Convert them to lower case
                word += (c ^ 32);
            }
            else {
                // insert
                if (word.length() != 0) {
                    RedBlackTree<string, int>::iterator it = rbt->find(word);
                    if (it == rbt->end()) {
                        // make a new entry
                        pair<string, int> newPair(word, 1);
                        rbt->insert(it, newPair);
                    }
                    else {
                        // word exists
                        ++it->second;
                        //cout << "iterated an existing pair" << endl;
                    }
                }
                word = "";
            }
        }
        // Don't forget to close the file.
        input_file.close();
    }

    catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    // Collect all words
    vector< pair<string, int> > words;
    for (RedBlackTree<string, int>::iterator it = rbt->begin(); it != rbt->end(); ++it) {
        words.push_back(make_pair(it->first, it->second));
    }
 
    // Sort the array
    stable_sort(words.begin(), words.end(), compare_pairs);

    display_stats(rbt, words, limit);
    delete rbt;

    return 0;
    }
