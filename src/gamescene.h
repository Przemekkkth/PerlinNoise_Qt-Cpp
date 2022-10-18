#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "game.h"
#include <QGraphicsPixmapItem>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);
    ~GameScene();

signals:

private:
    Game m_game;

    QGraphicsPixmapItem *pItem;

    // QGraphicsScene interface
    void updatePixmap();
    void renderGameScene();
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
