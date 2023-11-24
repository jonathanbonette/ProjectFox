#include "gamedata.h"

GameData::GameData() : player(nullptr), enemy(nullptr) {}

GameData* GameData::getInstance()
{
    static GameData instance;
    return &instance;
}

Character* GameData::getPlayer() const
{
    return player;
}

Character* GameData::getEnemy() const
{
    return enemy;
}

AttackResult GameData::getPlayerAttackResult() const
{
    return playerAttackResult;
}

AttackResult GameData::getEnemyAttackResult() const
{
    return enemyAttackResult;
}

void GameData::setPlayer(Character* newPlayer)
{
    player = newPlayer;
}

void GameData::setEnemy(Character* newEnemy)
{
    enemy = newEnemy;
}

void GameData::setPlayerAttackResult(const AttackResult& result)
{
    playerAttackResult = result;
}

void GameData::setEnemyAttackResult(const AttackResult& result)
{
    enemyAttackResult = result;
}
