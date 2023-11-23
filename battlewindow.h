#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QWidget>
#include "character.h"
#include <QLabel>
#include <QPushButton>

class BattleWindow : public QWidget
{
    Q_OBJECT

public:
    BattleWindow(QWidget *parent = nullptr);
    void setCharacters(Character *player, Character *enemy);

private slots:
    void startBattle();
    void attack();
    void usePotion();
    void initStep();

signals:
    void battleStarted(Character *player, Character *enemy);

private:
    Character *player;
    Character *enemy;
    QPushButton *startButton;
    QLabel *infoLabel;
    QPushButton *attackButton;
    QPushButton *potionButton;
};

#endif // BATTLEWINDOW_H
