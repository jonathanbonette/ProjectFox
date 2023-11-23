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

    // Test ***
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

    // Test ***
    int playerPotions;  // Número inicial de poções do jogador
    QLabel *playerHealthLabel;
    QLabel *enemyHealthLabel;
};

#endif // BATTLEWINDOW_H
