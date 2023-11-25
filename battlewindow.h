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
    // Adiciona o tipo de inimigo ao construtor da clase
    BattleWindow(QWidget *parent, const QString &enemyType);

    // Define os personagens que participarão da batalha
    void setCharacters(Character *player, Character *enemy);

private slots:
    // Slots para lidar com eventos de batalha
    void startBattle();
    void attack();
    void usePotion();
    void initStep();
    void updateHealthLabels();
    void checkBattleResult();

signals:
    // Sinal emitido quando a batalha é iniciada com os personagens definidos
    void battleStarted(Character *player, Character *enemy);

    void battleFinished();

private:
    // Personagens envolvidos na batalha
    Character *player;
    Character *enemy;

    // Rótulos para exibir informações durante a batalha
    QLabel *infoLabel;
    QLabel *playerHealthLabel;
    QLabel *enemyHealthLabel;
    QLabel *enemyImgLabel;
    QLabel *hpMessage;
    QLabel *resultAttackLabel;

    // Botões para ações durante a batalha
    QPushButton *startButton;
    QPushButton *attackButton;
    QPushButton *potionButton;

    // Layout para organizar os botões de ação
    QVBoxLayout *actionButtonLayout;

    // Número de poções que o jogador possui
    int playerPotions;

    // Armazena o tipo de inimigo
    QString enemyType;
};

#endif // BATTLEWINDOW_H
