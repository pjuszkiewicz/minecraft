//
// Created by Piotr Juszkiewicz on 11/01/2025.
//

#ifndef CROSSHAIR_H
#define CROSSHAIR_H


class Crosshair {

public:
    unsigned int VAO, VBO;

    Crosshair();

    void draw() const;
};


#endif //CROSSHAIR_H
