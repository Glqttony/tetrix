#include <cstring>

// Base class Piece
class Piece {
protected:
    int rotations[4][4][4];
    int color[3];
    int currentRotation;
    int x;
    int y;

public:
    // Constructor
    Piece(const int rotations[4][4][4], const int color[3])
        : currentRotation(0), x(30), y(0) {
        memcpy(this->rotations, rotations, 4 * 4 * 4 * sizeof(int));
        memcpy(this->color, color, 3 * sizeof(int));
    }

    // Rotate the piece
    void rotate(int rotation) {
        currentRotation = (currentRotation + rotation) % 4;
    }

    void setX(int newX) {
        x = newX;
    }

    void setY(int newY) {
        y = newY;
    }

    // Getters
    const int (*getCurrentShape() const)[4] {
        return rotations[currentRotation];
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    const int* getColor() const {
        return color;
    }

    int getCurrentRotation() const {
        return currentRotation;
    }
};

// Derived class for Tetris piece I
class PieceI : public Piece {
private:
    static const int rotationsI[4][4][4];
    static const int colorI[3];
public:
    PieceI()
        : Piece(rotationsI, colorI) {}
};

const int PieceI::rotationsI[4][4][4] = {
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    },
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    }
};

const int PieceI::colorI[3] = {0, 255, 255}; // Cyan color

// Derived class for Tetris piece O
class PieceO : public Piece {
private:
    static const int rotationsO[4][4][4];
    static const int colorO[3];
public:
    PieceO()
        : Piece(rotationsO, colorO) {}
};

const int PieceO::rotationsO[4][4][4] = {
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

const int PieceO::colorO[3] = {255, 255, 0}; // Yellow color

// Derived class for Tetris piece T
class PieceT : public Piece {
private:
    static const int rotationsT[4][4][4];
    static const int colorT[3];
public:
    PieceT()
        : Piece(rotationsT, colorT) {}
};

const int PieceT::rotationsT[4][4][4] = {
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};

const int PieceT::colorT[3] = {128, 0, 128}; // Purple color

// Derived class for Tetris piece S
class PieceS : public Piece {
private:
    static const int rotationsS[4][4][4];
    static const int colorS[3];
public:
    PieceS()
        : Piece(rotationsS, colorS) {}
};

const int PieceS::rotationsS[4][4][4] = {
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};

const int PieceS::colorS[3] = {0, 255, 0}; // Green color

// Derived class for Tetris piece Z
class PieceZ : public Piece {
private:
    static const int rotationsZ[4][4][4];
    static const int colorZ[3];
public:
    PieceZ()
        : Piece(rotationsZ, colorZ) {}
};

const int PieceZ::rotationsZ[4][4][4] = {
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

const int PieceZ::colorZ[3] = {255, 0, 0}; // Red color

// Derived class for Tetris piece J
class PieceJ : public Piece {
private:
    static const int rotationsJ[4][4][4];
    static const int colorJ[3];
public:
    PieceJ()
        : Piece(rotationsJ, colorJ) {}
};

const int PieceJ::rotationsJ[4][4][4] = {
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    }
};

const int PieceJ::colorJ[3] = {0, 0, 255}; // Blue color

// Derived class for Tetris piece L
class PieceL : public Piece {
private:
    static const int rotationsL[4][4][4];
    static const int colorL[3];
public:
    PieceL()
        : Piece(rotationsL, colorL) {}
};

const int PieceL::rotationsL[4][4][4] = {
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};

const int PieceL::colorL[3] = {255, 165, 0}; // Orange color
