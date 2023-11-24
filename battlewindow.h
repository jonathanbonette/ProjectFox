#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QWidget>
#include "character.h"
#include "qboxlayout.h"
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
    void updateHealthLabels();
    void checkBattleResult();

signals:
    void battleStarted(Character *player, Character *enemy);

private:
    Character *player;
    Character *enemy;
    QPushButton *startButton;
    QLabel *infoLabel;
    QPushButton *attackButton;
    QPushButton *potionButton;
    QLabel *playerHealthLabel;
    QLabel *enemyHealthLabel;
    QLabel *enemyImgLabel;
    QVBoxLayout *actionButtonLayout;
    int playerPotions;
    QLabel *hpMessage;

};

#endif // BATTLEWINDOW_H
