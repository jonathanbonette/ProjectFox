#include "gamedata.h"

// Inicialização dos membros de dados na construção
GameData::GameData() : player(nullptr), enemy(nullptr) {}

// Retorna a instância única da classe GameData (singleton)
GameData* GameData::getInstance()
{
    // Garante que apenas uma instância da classe seja criada
    static GameData instance;
    return &instance;
}

// Retorna o ponteiro para o personagem jogador
Character* GameData::getPlayer() const
{
    return player;
}

// Retorna o ponteiro para o personagem inimigo
Character* GameData::getEnemy() const
{
    return enemy;
}

// Retorna o resultado de ataque do jogador
AttackResult GameData::getPlayerAttackResult() const
{
    return playerAttackResult;
}

// Retorna o resultado de ataque do inimigo
AttackResult GameData::getEnemyAttackResult() const
{
    return enemyAttackResult;
}

// Configura o ponteiro para o personagem jogador
void GameData::setPlayer(Character* newPlayer)
{
    player = newPlayer;
}

// Configura o ponteiro para o personagem inimigo
void GameData::setEnemy(Character* newEnemy)
{
    enemy = newEnemy;
}

// Configura o resultado de ataque do jogador
void GameData::setPlayerAttackResult(const AttackResult& result)
{
    playerAttackResult = result;
}

// Configura o resultado de ataque do inimigo
void GameData::setEnemyAttackResult(const AttackResult& result)
{
    enemyAttackResult = result;
}
