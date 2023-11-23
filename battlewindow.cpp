#include "battlewindow.h"
#include <QVBoxLayout>

BattleWindow::BattleWindow(QWidget *parent)
    : QWidget(parent), player(nullptr), enemy(nullptr)
{
    // Configuração da tela de batalha
    setFixedSize(640, 480);
    QPixmap backgroundImage(":/images/assets/backgrounds/12.png");
    QPalette palette;
    palette.setBrush(backgroundRole(), backgroundImage);
    setPalette(palette);

    // Rótulo para exibir informações sobre a batalha
    infoLabel = new QLabel("Você iniciou uma batalha", this);
    infoLabel->setAlignment(Qt::AlignCenter);

    // Botão para iniciar a batalha
    startButton = new QPushButton("Iniciar Batalha", this);
    connect(startButton, &QPushButton::clicked, this, &BattleWindow::startBattle);

    // Botões para ações durante a batalha
    attackButton = new QPushButton("Atacar", this);
    potionButton = new QPushButton("Usar Potion", this);
    // Conecta os botões às respectivas funções
    connect(attackButton, &QPushButton::clicked, this, &BattleWindow::attack);
    connect(potionButton, &QPushButton::clicked, this, &BattleWindow::usePotion);

    // Layout horizontal para os botões (lado a lado)
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(attackButton);
    buttonLayout->addWidget(potionButton);

    // Layout vertical para organizar os elementos
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(buttonLayout);

    // Configura o layout principal
    setLayout(mainLayout);

    // Inicializa a primeira etapa
    initStep();
}

void BattleWindow::setCharacters(Character *p, Character *e)
{
    player = p;
    enemy = e;
}

void BattleWindow::startBattle()
{
    // qDebug() << "startBattle() called";

    // Lógica para ação após iniciar a batalha
    startButton->hide();
    attackButton->show();
    potionButton->show();
    infoLabel->hide();
}

void BattleWindow::attack()
{
    // Lógica para o ataque durante a batalha
}

void BattleWindow::usePotion()
{
    // Lógica para o uso de poção durante a batalha
}

void BattleWindow::initStep()
{
    // qDebug() << "initStep() called";

    // Mostra o texto inicial e o botão de iniciar
    infoLabel->setText("Você iniciou uma batalha");
    startButton->show();
    attackButton->hide();
    potionButton->hide();
}
