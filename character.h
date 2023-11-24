#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QRandomGenerator>
#include <QMessageBox>

struct AttackResult {
    QString message;
    int damage;
    bool hit;
};

class Character {


public:
    Character(const QString &name, int health, int attack, int defense);

    QString getName() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;

    AttackResult attackEnemy(Character &enemy);

    void takeDamage(int damage);
    void setHealth(int newHealth);

private:
    QString name;
    int health;
    int attack;
    int defense;

    int rollD20();
    int calculateChanceOfError();
};

class Archer : public Character {
public:
    Archer();
};

class Mage : public Character {
public:
    Mage();
};

class Paladin : public Character {
public:
    Paladin();
};

class Warrior : public Character {
public:
    Warrior();
};

class Enemy : public Character {
public:
    Enemy();
};

#endif // CHARACTER_H
