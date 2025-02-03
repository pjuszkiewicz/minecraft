//
// Created by Piotr Juszkiewicz on 05/01/2025.
//

#ifndef PAIR_HASH_H
#define PAIR_HASH_H

#include <iostream>

/// Funkcja hashująca do przechowywania mapy chunków
struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second) << 1;
    }
};

#endif //PAIR_HASH_H
