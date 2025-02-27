
#ifndef _SETJOINPARELLED_H_
#define _SETJOINPARELLED_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <string.h>
#include <queue>
#include <inttypes.h>
#include <sys/time.h>
#include <cmath>
#include <cstdio>

using namespace std;

// Macro to define the version of the algorithm. 
// If VERSION is set to 2, the bottomk variant is used.
#define VERSION 1

// Macros for hashing
#define PACK(x, y) ((x << 32) + y) // 32
#define PRIME 2017

#define EPS 1e-5

// Maximum number of threads that can be used
#define MAXTHREADNUM 128

// Type alias for token length. 
// Use unsigned int for ngram, unsigned short otherwise.
using TokenLen = unsigned int;

class SetJoinParelled {
public:
    double det;
    uint64_t resultNum = 0;    // Number of result pairs found  
    uint64_t candidateNum = 0; // Number of candidate pairs considered
    uint64_t listlens = 0;    
    TokenLen maxIndexPartNum;  // Maximum index partition number

    // Dataset containing records to be joined
    vector<vector<TokenLen>> dataset;

    // Array to store result pairs for each thread
    vector<pair<int, int>> result_pairs[MAXTHREADNUM];

    // Parameters related to calculation and dataset
    double coe;
    double ALPHA;
    unsigned int n;       // Number of records in the dataset
    unsigned int maxSize; // Maximum size of the records


    SetJoinParelled(vector<vector<TokenLen>> &sorted_records) {
        dataset = sorted_records;
    }

    ~SetJoinParelled() {
    }

    // Output the Parameters
    void showPara(){
        printf("det: %f coe: %f ALPHA: %f maxSize: %u maxIndexPartNum: %hu \n", det, coe, ALPHA, maxSize, maxIndexPartNum);
    }

    // Function to get the total number of result pairs found by all threads
    unsigned long long getResultPairsAmount(){
        unsigned long long pairs_amount = 0;
        for(int i = 0;i<MAXTHREADNUM;i++){
            pairs_amount += result_pairs[i].size();
        }
        return pairs_amount;
    }

    // Function to check overlap between two sets
    bool overlap(unsigned int x, unsigned int y, int posx = 0, int posy = 0, int current_overlap = 0);

    // Main function to perform set join
    void setjoin(double threshold);

    // Function to build index
    void index(double threshold);

    // Function to find candidate and similar pairs using a greedy approach
    void GreedyFindCandidateAndSimPairs(const int & tid, const int indexLenGrp, const unsigned int rid, const vector<unsigned int> &p_keys, const vector<unsigned int> &od_keys, const vector<TokenLen> &odk_st);

    // Function to find similar pairs
    void findSimPairs();

};

#endif