#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <crypto++/sha3.h>
#include <crypto++/hex.h>

using namespace std;

string generate_random_string(size_t length) {
    const string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string random_string;
    random_string.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        random_string += CHARACTERS[rand() % CHARACTERS.length()];
    }

    return random_string;
}

string sha3_256_hex(const string& input) {
    CryptoPP::SHA3_256 hash;
    string digest;
    CryptoPP::StringSource(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest), false)));
    return digest;
}

int calculate_score(const string& address) {
    int score = 0;

    for (size_t i = 0; i < address.size(); ++i) {
        if (address[i] == '0') {
            score += 10;
        } else {
            break;
        }
    }

    if (address.substr(0, 4) == "4444") {
        score += 40;

        if (address[4] != '4') {
            score += 20;
        }
    }

    if (address.size() >= 4 && address.substr(address.size() - 4) == "4444") {
        score += 20;
    }

    for (char c : address) {
        if (c == '4') {
            score += 1;
        }
    }

    return score;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<pair<int, pair<string, string>>> results;

    for (int i = 0; i < 1000000; ++i) {
        string salt = generate_random_string(12);

        string initcode = "0x94d114296a5af85c1fd2dc039cdaa32f1ed4b0fe0868f02d888bfc91feb645d9";
        string deployer = "0x48E516B34A1274f49457b9C6182097796D0498Cb";
        string data = deployer + initcode + salt;
        string hash = sha3_256_hex(data);
        string address = hash.substr(hash.size() - 40);

        int score = calculate_score(address);

        results.push_back({score, {salt, address}});
    }

    sort(results.begin(), results.end(), [](const pair<int, pair<string, string>>& a, const pair<int, pair<string, string>>& b) {
        return a.first > b.first;
    });

    ofstream outFile("/mnt/c/Users/Azriel/Desktop/uniswap_v4_addresses_sorted.txt");

    if (!outFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    for (const auto& result : results) {
        outFile << "Score: " << result.first
                << " | Salt: " << result.second.first
                << " | Address: 0x" << result.second.second << endl;

        cout << "Score: " << result.first
             << " | Salt: " << result.second.first
             << " | Address: 0x" << result.second.second << endl;
    }

    outFile.close();

    cout << "Sorted results saved to uniswap_v4_addresses_sorted.txt on your Desktop!" << endl;

    return 0;
}
