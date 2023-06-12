//
// Created by Виталия Степашкина on 10.04.2023.
//

#ifndef KDZ2_RANDOMIZER_H
#define KDZ2_RANDOMIZER_H
#include <vector>
#include <fstream>

class Randomizer {
public:
    std::vector<char> vec;

    void generateRandomVector(int size, int count) {
        vec = std::vector<char>(size);
        std::srand(time(0));
        char alphabet[] = {'A', 'B', 'C', 'D'};

        for (int i = 0; i < size; i++) {
            vec[i] = alphabet[rand() % count];
        }

    }

    std::vector<char> getRandArr(int x) {
        if (x == 0) {
            generateRandomVector(10000,2);
        }
        if (x == 1) {
            generateRandomVector(100000,2);
        }
        if (x == 2) {
            generateRandomVector(10000,4);
        }
        if (x == 3) {
            generateRandomVector(100000,4);
        }
        return vec;
    }
};
#endif //KDZ2_RANDOMIZER_H
