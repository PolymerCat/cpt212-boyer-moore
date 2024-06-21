#include <iostream> 
#include <string> 
#include <vector> 
#include <algorithm> 
using namespace std; 
#define NO_OF_CHARS 256 

// Preprocessing for Bad Character Heuristic 
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]) { 
    for (int i = 0; i < NO_OF_CHARS; i++) 
        badChar[i] = -1; 
    for (int i = 0; i < size; i++) 
        badChar[(int)str[i]] = i; 
} 

// Preprocessing for Good Suffix Heuristic 
void preprocessStrongSuffix(vector<int> &shift, vector<int> &borderPos, string pattern) { 
    int pattern_size = pattern.size(); 
    int i = pattern_size, j = pattern_size + 1; 
    borderPos[i] = j; 

    // start from last character in the pattern 
    while (i > 0) { 
        while (j <= pattern_size && pattern[i - 1] != pattern[j - 1]) { 
            if (shift[j] == 0) 
                shift[j] = j - i; 
            j = borderPos[j]; 
        } 
        i--; 
        j--; 
        borderPos[i] = j; 
    } 

} 

// Case for when the suffix does not appear in the pattern anymore 
void preprocessCase2(vector<int> &shift, vector<int> &borderPos, string pattern) { 
    int pattern_size = pattern.size(); 
    int j = borderPos[0]; 
    for (int i = 0; i <= pattern_size; i++) { 
        if (shift[i] == 0) 
            shift[i] = j; 
        if (i == j) 
            j = borderPos[j]; 
    } 

} 

  

void search(string txt, string pattern) { 
    int pattern_size = pattern.size(); 
    int txt_size = txt.size(); 

    // Bad Character Heuristic preprocessing 
    int badChar[NO_OF_CHARS]; 
    badCharHeuristic(pattern, pattern_size, badChar); 

    // Good Suffix Heuristic preprocessing 
    vector<int> borderPos(pattern_size + 1); 
    vector<int> shift(pattern_size + 1, 0); 
    preprocessStrongSuffix(shift, borderPos, pattern); 
    preprocessCase2(shift, borderPos, pattern); 

    int s = 0; 

    while (s <= (txt_size - pattern_size)) { 
        int j = pattern_size - 1; 
      
        // Reduce index j of pattern while characters match 
        while (j >= 0 && pattern[j] == txt[s + j]) 
            j--; 

        // If pattern is found 
        if (j < 0) { 
            cout << "Pattern occurs at shift = " << s << endl; 
            s += shift[0]; 
        } else { 
          
            // Shift the pattern based on the maximum of bad character heuristic and good suffix heuristic 
            s += max(shift[j + 1], j - badChar[txt[s + j]]); 

        } 

    } 

} 

  

int main() { 

    string txt = "ABAAABCDDEABCABCABC"; 

    string pattern = "ABC"; 

    search(txt, pattern); 

    return 0; 

} 
