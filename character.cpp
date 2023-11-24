#include "character.h"
#include "gamedata.h"

// Métodos dos personagens
Character::Character(const QString &name, int health, int attack, int defense)
    : name(name), health(health), attack(attack), defense(defense) {}

QString Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getAttack() const {
    return attack;
}

int Character::getDefense() const {
    return defense;
}

AttackResult Character::attackEnemy(Character& enemy, bool decide)
{
    // Estrutura que armazenará o resultado do ataque
    AttackResult result;

    // Estrutura de batalha
    int diceRoll = rollD20();
    int baseDamage = static_cast<int>(attack * 0.05) + diceRoll;
    double reductionFactor = 1.0 - (enemy.getDefense() / 100.0);
    int damage = std::max(1, static_cast<int>(baseDamage * reductionFactor));
    int hitError = calculateChanceOfError();

    // Verifica se o ataque foi bem-sucedido / true == player
    if(decide) {
        if (diceRoll == 1 || hitError <= diceRoll) {
            //        result.message = "Você tentou atacar, mas errou o alvo.";
            result.message = QString("O herói tentou atacar, mas errou o alvo.");
            result.damage = 0;
            result.hit = false;
        } else {
            enemy.takeDamage(damage);
            //        result.message = QString("Você atacou, causando %1 de dano.").arg(damage);
            result.message = QString("O herói atacou, causando %2 pontos de dano.").arg(damage);
            result.damage = damage;
            result.hit = true;
        }
    } else {
        // Similar ao bloco anterior, mas para ataques do inimigo
        if (diceRoll == 1 || hitError <= diceRoll) {
            //        result.message = "Você tentou atacar, mas errou o alvo.";
            result.message = QString("O inimigo tentou atacar, mas errou o alvo.");
            result.damage = 0;
            result.hit = false;
        } else {
            enemy.takeDamage(damage);
            //        result.message = QString("Você atacou, causando %1 de dano.").arg(damage);
            result.message = QString("O inimigo atacou, causando %2 pontos de dano.").arg(damage);
            result.damage = damage;
            result.hit = true;
        }
    }

    // Armazena o resultado no GameData
    GameData* gameData = GameData::getInstance();
    gameData->setPlayerAttackResult(result);

    return result;
}

// Reduz a saúde do personagem com base no dano recebido
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

// Métodos de chance de acerto e erro

int Character::rollD20() {
    return QRandomGenerator::global()->bounded(1, 21);
}

int Character::calculateChanceOfError() {
    return QRandomGenerator::global()->bounded(0, 101);
}

// Implementações das classes

Archer::Archer() : Character("Legolas", 90, 25, 12) {}

Mage::Mage() : Character("Gandalf", 110, 20, 15) {}

Paladin::Paladin() : Character("Bjorn", 100, 35, 20) {}

Warrior::Warrior() : Character("Arthur", 120, 35, 20) {}

Enemy::Enemy() : Character("Inimigo", 100, 30, 30) {}
