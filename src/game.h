#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QImage>

class Game
{
public:
    Game();
    ~Game();
    QImage image() const;
    void onInitImage();
    void onUpdateGame();
    QSize SCREEN = QSize(256, 256);
    QSize SCALE = QSize(3, 3);

    void increaseOctaveCount();
    void setMode(int value);
    void increaseScalingBias();
    void decreaseScalingBias();
    void randomizeBetween0and1();
    void randomizeBetweenMinus1and1();
private:

    void onCreateGame();

    void PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float fBias, float *fOutput);
    void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput);


    // 1D noise variables
    float *fNoiseSeed1D   = nullptr;
    float *fPerlinNoise1D = nullptr;
    int nOutputSize       = 256;

    // 2D noise variables
    int nOutputWidth      = 256;
    int nOutputHeight     = 256;
    float *fNoiseSeed2D   = nullptr;
    float *fPerlinNoise2D = nullptr;

    int nOctaveCount = 1;
    float fScalingBias = 2.0f;
    int nMode = 1;

    QImage m_image;
};

#endif // GAME_H
