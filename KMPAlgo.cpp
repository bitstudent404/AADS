#include <iostream>
#include <string>
using namespace std;

void computeLPS(string pattern, int lps[]) {
    int m = pattern.length();

    int len = 0;
    lps[0] = 0;

    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMP(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    int lps[m];

    computeLPS(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < n) {

        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            return i - j;
        }

        else if (i < n && text[i] != pattern[j]) {

            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return -1;
}

int main() {
    string text, pattern;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter pattern: ";
    getline(cin, pattern);

    int result = KMP(text, pattern);

    if (result != -1)
        cout << "Pattern found at index: " << result << endl;
    else
        cout << "Pattern not found" << endl;

    return 0;
}