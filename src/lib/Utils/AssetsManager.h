//
// Created by piotr on 17.01.25.
//

#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <string>

/// Zarządza miejsce przechowywania
class AssetsManager {
public:
    /// Zwraca lokalizacje głownego katalogu z assetami
    static std::string GetAssetsPath();
};


#endif //ASSETSMANAGER_H
