//simple program to analyze randomness bias of AES key generation using the sliding window technique

#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <array>
#include <iomanip>
#include <openssl/rand.h>

using namespace std;



// Function to generate a random AES-128 key
array<unsigned char, 16> generateAESKey() {
    array<unsigned char, 16> key; // 128-bit key

    if (RAND_bytes(key.data(), key.size()) != 1) {
        cerr << "Error generating random bytes\n";
       // return {"ERROR"};
        throw runtime_error("RAND_bytes failed");
    }

    cout << "AES-128 key (hex): ";
    for (unsigned char b : key) {
        cout << hex << setw(2) << setfill('0')
                  << static_cast<int>(b);
    }
    cout << "\n";
    return key;
}

// Sliding window function to find the length of the longest subarray with at most k distinct integers
int windowSLider(const vector<int>& nums, int k) {
    unordered_map<int, int> freqMap;
    int left = 0, right = 0;
    int maxLength = 0;

    while (right < nums.size()) {
        freqMap[nums[right]]++;

        while (freqMap.size() > k) {
            freqMap[nums[left]]--;
            if (freqMap[nums[left]] == 0) {
                freqMap.erase(nums[left]);
            }
            left++;
        }

        maxLength = max(maxLength, right - left + 1);
        right++;
    }

    return maxLength;
}

int main() {
    array<unsigned char, 16> aesKey = generateAESKey();
    vector<int> nums (aesKey.begin(), aesKey.end());
    //max distinct integers allowed
    int k = 1;
    int result = windowSLider(nums, k);
      cout << "======================================\n\n"<<endl;
    cout << "The length of the longest subarray with at most " << k << " distinct integers is: " << result << endl;

    cout << "======================================\n\n"<<endl;
    cout << "Generated AES Key in main (hex): ";
    for (unsigned char b : aesKey) {
        cout << hex << setw(2) << setfill('0')
                  << static_cast<int>(b)<<" ";

    }
    return 0;
}