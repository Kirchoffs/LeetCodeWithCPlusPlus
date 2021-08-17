#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    bool is_prefix;
    TrieNode* children[26];
    TrieNode() {
        is_prefix = false;
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
    
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != NULL) {
                delete children[i];
            }
        }
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }
    
    void insert(string prefix) {
        TrieNode* move = root;
        for (int i = 0; i < prefix.length(); i++) {
            int idx = prefix[i] - 'a';
            if (move->children[idx] == NULL) {
                move->children[idx] = new TrieNode();
            }
            move = move->children[idx];
            if (move->is_prefix) {
                return;
            }
        }
        move->is_prefix = true;
    }
    
    string find(string word) {
        TrieNode* move = root;
        for (int i = 0; i < word.length(); i++) {
            int idx = word[i] - 'a';
            if (move->children[idx] == NULL) {
                return word;
            }
            move = move->children[idx];
            if (move->is_prefix) {
                return word.substr(0, i + 1);
            }
        }
        return word;
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Trie trie;
        for (string& prefix: dictionary) {
            trie.insert(prefix);
        }
        
        istringstream is(sentence);
        string res = "";
        string token = "";
        while (is >> token) {
            res = res + trie.find(token) + " ";
        }
        
        if (res.size() > 0) {
            res.pop_back();
        }
        
        return res;
    }
};

int main() {
    vector<string> dictionary = {"cat", "bat", "rat"};
    string sentence = "the cattle was rattled by the battery";

    Solution solution;
    cout << solution.replaceWords(dictionary, sentence) << endl;
}