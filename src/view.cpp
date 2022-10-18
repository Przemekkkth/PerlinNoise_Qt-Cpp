#include "view.h"
#include <QDebug>

View::View()
    : m_gameScene(new GameScene(this))
{
    setScene(m_gameScene);
    resize(sceneRect().width() + 2, sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

View::~View()
{
    qDebug() << "~View()";
}
