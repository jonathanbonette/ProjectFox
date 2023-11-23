#include "battlewindow.h"
#include "gamedata.h"
#include <QVBoxLayout>
#include <QMovie>

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

    // Test ***
    // Criação dos rótulos de saúde
    playerHealthLabel = new QLabel(this);
    enemyHealthLabel = new QLabel(this);
    playerHealthLabel->setAlignment(Qt::AlignTop);
    enemyHealthLabel->setAlignment(Qt::AlignTop);

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

    // Test ***
    // Configurar o jogador no GameData
    GameData *gameData = GameData::getInstance();

    // Cria instâncias dos personagens (exemplo: Guerreiro e Inimigo Peludo)
    Character *player = new Character("Asgorn", 100, 20, 10);
    Character *enemy = new Character("Inimigo Peludo", 80, 15, 8);

    gameData->setPlayer(player);
    // Configurar o inimigo no GameData
    gameData->setEnemy(enemy);

    // Inicializa a primeira etapa
    initStep();
}

void BattleWindow::startBattle()
{
    // Lógica para ação após iniciar a batalha
    startButton->hide();
    attackButton->show();
    potionButton->show();
    infoLabel->hide();

    // Adiciona a imagem animada do inimigo
    QLabel *enemyImg = new QLabel(this);
    QMovie *enemyMovie = new QMovie(":/images/assets/monster/reptile/idle.gif");
    enemyImg->setMovie(enemyMovie);
    enemyMovie->start();
    enemyImg->setAlignment(Qt::AlignCenter);

    // Define o tamanho desejado
    enemyImg->setScaledContents(true);

    // Adicione o QLabel ao layout principal
    layout()->addWidget(enemyImg);
}

void BattleWindow::attack()
{
    // Lógica para o ataque durante a batalha
    // Obtém as instâncias dos personagens do GameData
    GameData* gameData = GameData::getInstance();
    player = gameData->getPlayer();
    enemy = gameData->getEnemy();

    // Test ***
    // Lógica para o ataque durante a batalha
    AttackResult playerResult = player->attackEnemy(*enemy);
    updateHealthLabels();  // Atualiza os rótulos de saúde

    // Exibe mensagem de resultado do ataque do jogador
    infoLabel->setText(playerResult.message);

    // Lógica para a resposta do inimigo
    if (enemy->getHealth() > 0) {
        AttackResult enemyResult = enemy->attackEnemy(*player);
        updateHealthLabels();  // Atualiza os rótulos de saúde após o ataque do inimigo

        // Adiciona a mensagem de resultado do ataque do inimigo ao texto existente
        infoLabel->setText(infoLabel->text() + "\n" + enemyResult.message);
    }

    // Verifica se a batalha terminou
    checkBattleResult();
}

void BattleWindow::usePotion()
{
    // Lógica para o uso de poção durante a batalha
}

void BattleWindow::initStep()
{
    qDebug() << "initStep() called";

    // Mostra o texto inicial e o botão de iniciar
    infoLabel->setText("Você iniciou uma batalha");
    startButton->show();
    attackButton->hide();
    potionButton->hide();
}

void BattleWindow::updateHealthLabels()
{
    // Test  ***
    // Atualiza os rótulos com informações de saúde dos personagens
    GameData* gameData = GameData::getInstance();
    Character* playerCharacter = gameData->getPlayer();
    Character* enemyCharacter = gameData->getEnemy();

    if(playerCharacter && enemyCharacter){
        qDebug() << playerCharacter->getHealth();
        playerHealthLabel->setText(QString("Jogador:\nSaúde: %1").arg(playerCharacter->getHealth()));
        enemyHealthLabel->setText(QString("Inimigo:\nSaúde: %1").arg(enemyCharacter->getHealth()));

    } else {
        qDebug() << "player and enemy not working";
    }
}

void BattleWindow::checkBattleResult()
{
    // Verifica se a batalha terminou (saúde de jogador ou inimigo <= 0)
    GameData* gameData = GameData::getInstance();
    player = gameData->getPlayer();
    enemy = gameData->getEnemy();

    if (player->getHealth() <= 0 || enemy->getHealth() <= 0) {
        QString resultMessage;
        if (player->getHealth() <= 0) {
            resultMessage = "Você foi derrotado!";
        } else {
            resultMessage = "Você venceu!";
        }
        QMessageBox::information(this, "Fim da Batalha", resultMessage);
        close();  // Fecha a janela de batalha
    }
}
