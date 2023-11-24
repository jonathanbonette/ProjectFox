#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "dialogwindow.h"
#include "character.h"

class GameData
{
public:
    // Retorna a instância única da classe GameData (singleton)
    static GameData* getInstance();

    // Métodos para obter os personagens (jogador e inimigo)
    Character* getPlayer() const;
    Character* getEnemy() const;

    // Métodos para obter os resultados de ataque dos personagens
    AttackResult getPlayerAttackResult() const;
    AttackResult getEnemyAttackResult() const;

    // Métodos para configurar os personagens
    void setPlayer(Character* player);
    void setEnemy(Character* enemy);

    // Métodos para configurar os resultados de ataque dos personagens
    void setPlayerAttackResult(const AttackResult& result);
    void setEnemyAttackResult(const AttackResult& result);

    // Test ***
    // Métodos para configurar e obter a janela de diálogo
    void setDialogWindow(DialogWindow* dialogWindow) {
        this->dialogWindow = dialogWindow;
    }

    DialogWindow* getDialogWindow() const {
        return dialogWindow;
    }

private:
    // Construtor privado para evitar instâncias múltiplas
    GameData();

    // Membros para armazenar os personagens e resultados de ataque
    Character* player;
    Character* enemy;
    AttackResult playerAttackResult;
    AttackResult enemyAttackResult;

    // Test ***
    // Membro para armazenar a janela de diálogo
    DialogWindow* dialogWindow;
};

#endif // GAMEDATA_H
