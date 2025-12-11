/*
 * Name1: Samaa Mehrez Abdelhamid    ID1: 20230177
 * Name2: Mariam Ayman Mosaad        ID2: 20230390
 * Name3: Klara Sameh Wadie          ID3: 20230294
 */
#include <iostream>
using namespace std;

struct Suffix
{
    int ind; // index of suffix
    int r1;  // the current order of the suffix.
    int r2;  // the order that will be used in case there is a tie in r1.
};

// Compare Function for Merge Sort
int CompareSuffix(Suffix &s1, Suffix &s2)
{
    // Compare first rank
    if (s1.r1 < s2.r1) return -1;
    if (s1.r1 > s2.r1) return 1;

    // If first ranks are equal, compare second rank
    if (s1.r2 < s2.r2) return -1;
    if (s1.r2 > s2.r2) return 1;

    return 0; // both ranks are equal
}

// Merge function for Merge Sort
void Merge(Suffix* suffix, int left, int middle, int right)
{
    int n1 = middle - left + 1; // size of left subarray
    int n2 = right - middle;    // size of right subarray

    Suffix* L = new Suffix[n1]; // temporary left array
    Suffix* R = new Suffix[n2]; // temporary right array

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = suffix[left + i];
    for (int i = 0; i < n2; i++) R[i] = suffix[middle + 1 + i];

    int i = 0, j = 0, k = left;

    // Merge back to original array in sorted order
    while (i < n1 && j < n2)
    {
        if (CompareSuffix(L[i], R[j]) <= 0)
            suffix[k++] = L[i++];
        else
            suffix[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1) suffix[k++] = L[i++];
    while (j < n2) suffix[k++] = R[j++];

    // Free temporary arrays
    delete[] L;
    delete[] R;
}

// Merge Sort
void MergeSort(Suffix* suffix, int left, int right)
{
    if (left >= right) return; // base case: one element

    int m = (left + right) / 2; // middle index

    MergeSort(suffix, left, m);      // sort left half
    MergeSort(suffix, m + 1, right); // sort right half
    Merge(suffix, left, m, right);   // merge the two halves
}

class SuffixArray
{
private:
    char* text;   // input text
    int n;        // length of text
    int* sa;      // final suffix array
    int* rank;    // rank array for each suffix
    Suffix* suffix; // array of suffixes

    // Compute length
    int TextLength(const char* s)
    {
        int i = 0;
        while (s[i] != '\0') i++;
        return i;
    }

    // Copy string into new memory
    char* CopyText(const char* s)
    {
        int len = TextLength(s);
        char* t = new char[len + 1];
        for (int i = 0; i < len; i++) t[i] = s[i];
        t[len] = '\0';
        return t;
    }

public:

    SuffixArray(const char* s)
    {
        text = CopyText(s);         // copy input text
        n = TextLength(text);       // store length
        sa = new int[n];            // allocate suffix array
        rank = new int[n];          // allocate rank array
        suffix = new Suffix[n];     // allocate suffix triplets
    }

    ~SuffixArray()
    {
        delete[] text;
        delete[] sa;
        delete[] rank;
        delete[] suffix;
    }

    // Construct Suffix Array using Prefix Doubling
    void ConstructUsingPrefixDoubling()
    {
        // Initialize ranks based on ASCII values
        for (int i = 0; i < n; i++)
        {
            rank[i] = (int)(unsigned char)text[i] + 1; // rank > 0
        }

        int* newRank = new int[n]; // temporary array for new ranks
        int k = 1;                 // current prefix length

        while (true)
        {
            // Build suffixes (index, r1-> rank[i], r2-> rank[i+k])
            for (int i = 0; i < n; i++)
            {
                suffix[i].ind = i;
                suffix[i].r1 = rank[i];
                suffix[i].r2 = (i + k < n ? rank[i + k] : 0); // 0 if past end
            }

            // Sort suffixes by (r1, r2) using Merge Sort
            MergeSort(suffix, 0, n - 1);

            // Assign new ranks
            int r = 1;
            newRank[suffix[0].ind] = r;
            for (int i = 1; i < n; i++)
            {
                if (suffix[i].r1 != suffix[i - 1].r1 || suffix[i].r2 != suffix[i - 1].r2)
                    r++; // increase rank if different from previous
                newRank[suffix[i].ind] = r;
            }

            // Update rank array
            for (int i = 0; i < n; i++)
                rank[i] = newRank[i];

            k = k * 2; // double prefix length for next iteration

            // Stop if all suffixes have unique ranks
            if (r == n) break;
        }

        // Build final suffix array from sorted suffixes
        for (int i = 0; i < n; i++)
            sa[i] = suffix[i].ind;

        delete[] newRank;
    }

    // Print the suffix array
    void Print()
    {
        for (int i = 0; i < n; i++)
        {
            if (i > 0) cout << " ";
            cout << sa[i];
        }
        cout << "\n";
    }
};

// ----------------------------
// Main
// ----------------------------
int main()
{
    SuffixArray t("ACGACTACGATAAC$"); // create object for this string
    t.ConstructUsingPrefixDoubling(); // build suffix array
    t.Print();                        // print suffix array
    // Expected output: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5
    return 0;
}

