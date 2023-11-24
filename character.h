#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QRandomGenerator>
#include <QMessageBox>

// Estrutura que representa o resultado de um ataque
struct AttackResult {
    QString message;    // Mensagem descrevendo o resultado do ataque
    int damage;         // Quantidade de dano causado
    bool hit;           // Indica se o ataque acertou
};

// Classe base para personagens
class Character {
public:
    // Construtor que inicializa as características básicas do personagem
    Character(const QString &name, int health, int attack, int defense);

    // Métodos de acesso para obter informações sobre o personagem
    QString getName() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;

    // Método para realizar um ataque a outro personagem
    AttackResult attackEnemy(Character &enemy, bool decide = true);

    // Método para reduzir a saúde do personagem com base no dano recebido
    void takeDamage(int damage);

    // Método para definir a saúde do personagem
    void setHealth(int newHealth);

private:
    // Informações do personagem
    QString name;
    int health;
    int attack;
    int defense;

    int rollD20();                  // Método para rolar um dado D20
    int calculateChanceOfError();   // Método para calcular a chance de erro ao atacar
};

// Classes derivadas representando tipos específicos de personagens

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
