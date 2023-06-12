//
// Created by Виталия Степашкина on 9.04.2023.
//

#ifndef KDZ2_ALGO_H
#define KDZ2_ALGO_H

#include <vector>
#include <string>
#include <cmath>

class FindSubstr {
public:
    virtual int find(std::string &pattern, std::string &str) {
    }

    virtual std::string getName() {
        return "Origin";
    }
};

class SimpleFind : public FindSubstr {
public:
    virtual int find(std::string &pattern, std::string &str) {
        int ind = -1;
        for (int i = 0; i <= str.length() - pattern.length(); i++) {
            int j;
            for (j = 0; j < pattern.length(); j++) {
                if (pattern[j] != '?' && str[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == pattern.length()) {
                ind = i;
            }
        }
        return ind;
    }
    std::string getName() {
        return "Simple find";
    }
};

class StandartKMP : public FindSubstr {
public:
    std::vector<int> standard_borders(std::string &pattern) {
        std::vector<int> p(pattern.size(), 0);
        for (size_t i = 1; i < pattern.size(); ++i) {
            size_t k = p[i - 1];
            while (k > 0 && pattern[i] != pattern[k] && pattern[i] != '?' && pattern[k] != '?') {
                k = p[k - 1];
            }
            if (pattern[i] == pattern[k] || pattern[i] == '?' || pattern[k] == '?') {
                k++;
            }
            p[i] = k;
        }
        return p;
    }

    virtual int find(std::string &pattern, std::string &str) {
        std::vector<int> borders = standard_borders(pattern);
        int ind = -1, j = 0;
        for (int i = 0; i < str.length(); i++) {
            while (j > 0 && str[i] != pattern[j] && pattern[j] != '?') {
                j = borders[j - 1];
            }
            if (str[i] == pattern[j] || pattern[j] == '?') {
                ++j;
            }
            if (j == pattern.length()) {
                ind = i - pattern.length() + 1;
                //std::cout<<ind<<std::endl;
                j = borders[j - 1];
            }
        }
        return ind;
    }

    std::string getName() {
        return "KMP";
    }
};

class FineKMP : public FindSubstr {
public:
    std::vector<int> sophisticated_borders(std::string &pattern) {
        std::vector<int> borders(pattern.size(), 0);
        std::vector<int> bordersSoph(pattern.size(), 0);;
        for (int i = 1; i < pattern.size(); ++i) {
            int j = borders[i - 1];
            while (j > 0 && pattern[i] != pattern[j] && pattern[i] != '?' && pattern[j] != '?') {
                j = borders[j - 1];
            }
            if (pattern[i] == pattern[j] || pattern[i] == '?' || pattern[j] == '?') {
                j++;
            }
            borders[i] = j;
        }

        for (int i = 1; i < pattern.size() - 1; ++i) {
            if (pattern[borders[i]] != pattern[i + 1] && pattern[borders[i]] != '?' && pattern[i + 1] != '?') {
                bordersSoph[i] = borders[i];
            } else {
                bordersSoph[i] = bordersSoph[borders[i - 1]];
            }
        }
        return bordersSoph;
    }

    virtual int find(std::string &pattern, std::string &str) {
        std::vector<int> bordersSoph = sophisticated_borders(pattern);
        int ind = -1, j = 0;
        for (int i = 0; i < str.length(); ++i) {
            while (j > 0 && str[i] != pattern[j] && pattern[j] != '?') {
                j = bordersSoph[j - 1];
            }
            if (str[i] == pattern[j] || pattern[j] == '?') {
                ++j;
            }
            if (j == pattern.length()) {
                ind = i - pattern.length() + 1;
                j = bordersSoph[j - 1];
            }
        }
        return ind;
    }
    std::string getName() {
        return "Sophisticated KMP";
    }
};

//Алгоритм Бойера-Мура
class BoierMur : public FindSubstr {
public:
    void badChar(std::string &pattern, std::vector<int> &badchar) {
        for (int i = 0; i < pattern.size(); i++) {
            if (pattern[i] != '?') {
                badchar[(int) pattern[i]] = i;
            }
        }
    }

    virtual int find(std::string &pattern, std::string &str) {
        std::vector<int> badchar(160, -1);
        badChar(pattern, badchar);
        int s = 0, ind = -1;
        while (s <= (str.length() - pattern.length())) {
            int j = pattern.length() - 1;
            while (j >= 0 && (pattern[j] == str[s + j] || pattern[j] == '?')) {
                --j;
            }
            if (j < 0) {
                ind = s;
                s += (s + pattern.length() < str.length()) ? pattern.length() - badchar[str[s + pattern.length()]] : 1;
            } else {
                s += std::max(1, j - badchar[str[s + j]]);
            }
        }
        return ind;
    }

    std::string getName() {
        return "Boier Mur";
    }
};

#endif //KDZ2_ALGO_H
