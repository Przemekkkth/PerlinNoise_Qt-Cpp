#include "game.h"
#include <QDebug>

Game::Game()
{
    onCreateGame();
    onInitImage();
}

Game::~Game()
{
    qDebug() << "~Game()";
    delete[] fNoiseSeed2D;
    delete[] fPerlinNoise2D;
    delete[] fNoiseSeed1D;
    delete[] fPerlinNoise1D;
}

QImage Game::image() const
{
    return m_image;
}

void Game::onInitImage()
{
    m_image = QImage(SCREEN, QImage::Format_RGB32);
    m_image.fill(QColor(Qt::black));
}

void Game::onCreateGame()
{
    nOutputWidth = SCREEN.width();
    nOutputHeight = SCREEN.height();

    fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
    fPerlinNoise2D = new float[nOutputWidth * nOutputHeight];
    for(int i = 0; i < nOutputWidth*nOutputHeight; ++i)
    {
        fNoiseSeed2D[i] = (float)rand()/(float)RAND_MAX;
    }

    nOutputSize = SCREEN.width();
    fNoiseSeed1D = new float[nOutputSize];
    fPerlinNoise1D = new float[nOutputSize];
    for(int i = 0; i < nOutputSize; i++)
    {
        fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
    }


}

void Game::onUpdateGame()
{
    if(nMode == 1)
    {

        PerlinNoise1D(nOutputSize, fNoiseSeed1D, nOctaveCount, fScalingBias, fPerlinNoise1D);

        for (int x = 0; x < nOutputSize; x++)
        {
            int y = -(fPerlinNoise1D[x] * (float)SCREEN.height() / 2.0f) + (float)SCREEN.height() / 2.0f;
            if (y < SCREEN.height() / 2)
                for (int f = y; f < SCREEN.height() / 2; f++)
                {
                    m_image.setPixelColor(x, f, QColor(Qt::green));
                }
            else
                for (int f = SCREEN.height() / 2; f <= y; f++)
                {
                    m_image.setPixelColor(x, f, QColor(Qt::red));
                }
        }
    }
    else if(nMode == 2)
    {
        PerlinNoise2D(nOutputWidth, nOutputHeight, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);

        for (int x = 0; x < nOutputWidth; x++)
        {
            for (int y = 0; y < nOutputHeight; y++)
            {
                int pixel_bw = (int)(fPerlinNoise2D[y * nOutputWidth + x] * 12.0f);
                QColor pixelColor = QColor(0,0,0);
                switch (pixel_bw)
                {
                case 0:
                    pixelColor = QColor(16, 12, 7);
                    break;

                case 1:
                    pixelColor = QColor(39, 35, 32);
                    break;
                case 2:
                    pixelColor = QColor(62, 59, 57);
                    break;
                case 3:
                    pixelColor = QColor(85, 82, 80);
                    break;
                case 4:
                    pixelColor = QColor(109, 106, 106);
                    break;

                case 5:
                    pixelColor = QColor(133, 131, 128);
                    break;
                case 6:
                    pixelColor = QColor(155, 154, 156);
                    break;
                case 7:
                    pixelColor = QColor(178, 174, 170);
                    break;
                case 8:
                    pixelColor = QColor(201, 201, 205);
                    break;

                case 9:
                    pixelColor = QColor(222, 220, 222);
                    break;
                case 10:
                    pixelColor = QColor(232, 230, 232);
                    break;
                case 11:
                    pixelColor = QColor(248, 248, 255);
                    break;
                case 12:
                    pixelColor = QColor(255, 255, 255);
                    break;
                }

                m_image.setPixelColor(x,y, pixelColor);
            }
        }
    }
    else if(nMode == 3)
    {
        PerlinNoise2D(nOutputWidth, nOutputHeight, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);
        for (int x = 0; x < nOutputWidth; x++)
        {
            for (int y = 0; y < nOutputHeight; y++)
            {
                QColor pixelColor = QColor(0,0,0);
                int pixel_bw = (int)(fPerlinNoise2D[y * nOutputWidth + x] * 16.0f);
                switch (pixel_bw)
                {
                case 0:
                    pixelColor = QColor(17, 107, 250);
                    break;

                case 1:
                    pixelColor = QColor(26, 106, 235);
                    break;
                case 2:
                    pixelColor = QColor(34, 114, 227);
                    break;
                case 3:
                    pixelColor = QColor(42, 132, 222);
                    break;
                case 4:
                    pixelColor = QColor(45, 137, 207);
                    break;

                case 5:
                    pixelColor = QColor(21, 185, 235);
                    break;
                case 6:
                    pixelColor = QColor(26, 200, 219);
                    break;
                case 7:
                    pixelColor = QColor(33, 198, 204);
                    break;
                case 8:
                    pixelColor = QColor(33, 204, 178);
                    break;

                case 9:
                    pixelColor = QColor(7, 245, 39);
                    break;
                case 10:
                    pixelColor = QColor(59, 237, 19);
                    break;
                case 11:
                    pixelColor = QColor(94, 227, 27);
                    break;
                case 12:
                    pixelColor = QColor(126, 201, 34);
                    break;

                case 13:
                    pixelColor = QColor(126, 201, 34);
                    break;
                case 14:
                    pixelColor = QColor(77, 73, 73);
                    break;
                case 15:
                    pixelColor = QColor(122, 116, 116);
                    break;
                case 16:
                    pixelColor = QColor(227, 220, 220);
                    break;
                }
                m_image.setPixelColor(x,y, pixelColor);
            }
        }
    }
}

void Game::increaseOctaveCount()
{
    nOctaveCount++;
    if (nOctaveCount == 9)
    {
        nOctaveCount = 1;
    }
    qDebug() << "nOctaveCount " << nOctaveCount;
}

void Game::setMode(int value)
{
    if(value == 1)
    {
        nMode = 1;
    }
    else if(value == 2)
    {
        nMode = 2;
    }
    else
    {
        nMode = 3;
    }
    qDebug() << "nMode " << nMode;
}

void Game::increaseScalingBias()
{
    fScalingBias += 0.2f;
    qDebug() << "fScalingBias " << fScalingBias;
}

void Game::decreaseScalingBias()
{
    fScalingBias -= 0.2f;
    if(fScalingBias < 0.2f)
    {
        fScalingBias = 0.2f;
    }
    qDebug() << "fScalingBias " << fScalingBias;
}

void Game::randomizeBetween0and1()
{
    if(nMode == 1)
    {
        for (int i = 0; i < nOutputSize; i++)
        {
            fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
        }
    }
    else if(nMode == 2)
    {
        for (int i = 0; i < nOutputWidth * nOutputHeight; i++)
        {
            fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
        }
    }
    else
    {
        for (int i = 0; i < nOutputWidth * nOutputHeight; i++)
        {
            fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
        }
    }
}

void Game::randomizeBetweenMinus1and1()
{
    if(nMode == 1)
    {
        for (int i = 0; i < nOutputSize; i++)
        {
            fNoiseSeed1D[i] = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
        }
    }
}

void Game::PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float fBias, float *fOutput)
{
    // Used 1D Perlin Noise
    for (int x = 0; x < nCount; x++)
    {
        float fNoise = 0.0f;
        float fScaleAcc = 0.0f;
        float fScale = 1.0f;

        for (int o = 0; o < nOctaves; o++)
        {
            int nPitch = nCount >> o;// if nCount = 256 -> 256 >> 0 = 256, 256 >> 1 = 128, 256 >> 2 = 64
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % nCount;

            float fBlend = (float)(x - nSample1) / (float)nPitch;

            float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

            fScaleAcc += fScale;
            fNoise += fSample * fScale;
            fScale = fScale / fBias;
        }

        // Scale to seed range
        fOutput[x] = fNoise / fScaleAcc;
    }
}

void Game::PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput)
{
    for(int x = 0; x < nWidth; x++)
    {
        for(int y = 0; y < nHeight; y++)
        {
            float fNoise    = 0.0f;
            float fScaleAcc = 0.0f;
            float fScale    = 1.0f;

            for(int o = 0; o < nOctaves; o++)
            {
                int nPitch = nWidth >> o;
                int nSampleX1 = (x / nPitch) * nPitch;
                int nSampleY1 = (y / nPitch) * nPitch;

                int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
                int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

                float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
                float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

                float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
                float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

                fScaleAcc += fScale;
                fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                fScale = fScale / fBias;
            }
            // Scale to seed range
            fOutput[y * nWidth + x] = fNoise / fScaleAcc;
        }
    }
}

