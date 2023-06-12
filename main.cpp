#include <vector>
#include <iostream>
#include "algo.h"
#include "Randomizer.h"

void launch(Randomizer rand, std::vector<FindSubstr *> finders) {
    std::vector<std::string> item = {"2-letter, 10000", "2-letter, 1000000", "4-letter, 10000", "4-letter, 1000000"};
    std::ofstream fsmall("../smallArr.csv");
    fsmall << "Size;";
    for (int i = 0; i < item.size(); ++i) {
        for (int k = 0; k <= 4; ++k) {
            for (int j = 0; j < finders.size(); ++j) {
                fsmall << finders[j]->getName() << " " << item[i] << ", " << k << "-'?';";
            }
        }
    }
    fsmall << "\n";
    for (int i = 100; i <= 3000; i += 100) {
        fsmall << i << ";";
        for (int j = 0; j < 4; ++j) {
            std::vector<char> arr = rand.getRandArr(j);
            std::string text(arr.begin(), arr.end());
            for (int k = 0; k <= 4; ++k) {
                std::srand(time(NULL));
                int pos = std::rand() % 7000;
                std::string pattern = text.substr(pos, i);
                for (int l = 0; l < k; l++) {
                    pattern[std::rand() % (pattern.length())] = '?';
                }
                for (int ind = 0; ind < finders.size(); ++ind) {
                    int64_t microseconds = 0;
                    for (int h = 0; h < 20; ++h) {
                        auto start = std::chrono::high_resolution_clock::now();
                        finders[ind]->find(pattern, text);
                        auto elapsed = std::chrono::high_resolution_clock::now() - start;
                        microseconds += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                    }

                    fsmall << std::max(microseconds / 20, 1ll) << ";";
                }
            }
        }
        fsmall << "\n";
    }
    fsmall.close();
}

int main() {
    std::vector<FindSubstr *> finders;
    finders.push_back(new SimpleFind());
    finders.push_back(new StandartKMP());
    finders.push_back(new FineKMP());
    finders.push_back(new BoierMur());
    Randomizer rand = Randomizer();
    launch(rand, finders);
//     FindSubstr* kmp= new StandartKMP();
//    std::string pattern="ab?";
//    std::string test="abccabbababjjh";
//    kmp->find(pattern,test);
    return 0;
}