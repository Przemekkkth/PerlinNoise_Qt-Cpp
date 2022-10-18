#include "gamescene.h"
#include <QKeyEvent>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(0,0, m_game.SCREEN.width() * m_game.SCALE.width(), m_game.SCREEN.height() * m_game.SCALE.height());

    pItem = new QGraphicsPixmapItem();
    addItem(pItem);

    updatePixmap();
}

void GameScene::updatePixmap()
{
    m_game.onInitImage();
    m_game.onUpdateGame();
    pItem->setPixmap(QPixmap::fromImage(m_game.image()).scaled(m_game.SCREEN.width() * m_game.SCALE.width(), m_game.SCREEN.height() * m_game.SCALE.height()) );
}

void GameScene::renderGameScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

GameScene::~GameScene()
{
    qDebug() << "~GameScene()";
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        switch (event->key()) {
        case Qt::Key_Z:
        {
            m_game.randomizeBetween0and1();
            updatePixmap();
        }
            break;
        case Qt::Key_X:
        {
            m_game.randomizeBetweenMinus1and1();
            updatePixmap();
        }
            break;
        case Qt::Key_Space:
        {
            m_game.increaseOctaveCount();
            updatePixmap();
        }
            break;
        case Qt::Key_1:
        {
            m_game.setMode(1);
            updatePixmap();
        }
            break;
        case Qt::Key_2:
        {
            m_game.setMode(2);
            updatePixmap();
        }
            break;
        case Qt::Key_3:
        {
            m_game.setMode(3);
            updatePixmap();
        }
            break;
        case Qt::Key_Q:
        {
            m_game.increaseScalingBias();
            updatePixmap();
        }
            break;
        case Qt::Key_A:
        {
            m_game.decreaseScalingBias();
            updatePixmap();
        }
            break;
        case Qt::Key_P:
        {
            renderGameScene();
        }
            break;
        }
    }

    QGraphicsScene::keyReleaseEvent(event);
}
