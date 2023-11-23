#include "character.h"

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

AttackResult Character::attackEnemy(Character &enemy) {
    AttackResult result;

    int diceRoll = rollD20();
    int baseDamage = static_cast<int>(attack * 0.05) + diceRoll;
    double reductionFactor = 1.0 - (enemy.getDefense() / 100.0);
    int damage = std::max(1, static_cast<int>(baseDamage * reductionFactor));
    int hitError = calculateChanceOfError();

    if (diceRoll == 1 || hitError <= diceRoll) {
        result.message = QString("%1 tentou atacar %2, mas errou o alvo.")
                             .arg(name)
                             .arg(enemy.getName());
        result.damage = 0;
        result.hit = false;
        return result;
    }

    enemy.takeDamage(damage);

    result.message = QString("%1 atacou %2 causando %3 de dano.")
                         .arg(name)
                         .arg(enemy.getName())
                         .arg(damage);
    result.damage = damage;
    result.hit = true;

    return result;
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

int Character::rollD20() {
    return QRandomGenerator::global()->bounded(1, 21);
}

int Character::calculateChanceOfError() {
    return QRandomGenerator::global()->bounded(0, 101);
}

Archer::Archer() : Character("Legolas", 90, 25, 12) {}

Mage::Mage() : Character("Gandalf", 110, 20, 15) {}

Paladin::Paladin() : Character("Bjorn", 100, 35, 20) {}

Warrior::Warrior() : Character("Arthur", 120, 35, 20) {}

Enemy::Enemy() : Character("Inimigo", 100, 30, 30) {}
