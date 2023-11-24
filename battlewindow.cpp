#include "battlewindow.h"
#include "gamedata.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMovie>
#include <QDebug>

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
    infoLabel->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    infoLabel->setFont(QFont("System", 24, QFont::Bold));
    infoLabel->setStyleSheet("color: white;");

    // Botão para iniciar a batalha
    startButton = new QPushButton("Iniciar Batalha", this);
    connect(startButton, &QPushButton::clicked, this, &BattleWindow::startBattle);

    // Botões para ações durante a batalha
    attackButton = new QPushButton("Atacar", this);
    potionButton = new QPushButton("Usar Potion", this);
    // Conecta os botões às respectivas funções
    connect(attackButton, &QPushButton::clicked, this, &BattleWindow::attack);
    connect(potionButton, &QPushButton::clicked, this, &BattleWindow::usePotion);

    // Criação dos rótulos de saúde
    playerHealthLabel = new QLabel(this);
    enemyHealthLabel = new QLabel(this);
    playerHealthLabel->setAlignment(Qt::AlignTop);
    enemyHealthLabel->setAlignment(Qt::AlignTop);
    playerHealthLabel->setFont(QFont("System", 24, QFont::Bold));
    playerHealthLabel->setStyleSheet("color: white;");
    enemyHealthLabel->setFont(QFont("System", 24, QFont::Bold));
    enemyHealthLabel->setStyleSheet("color: white;");

    // Criação de um QLabel para exibir mensagens dinâmicas
    hpMessage = new QLabel(this);
    hpMessage->setAlignment(Qt::AlignTop);
    hpMessage->setFont(QFont("System", 24, QFont::Bold));
    hpMessage->setStyleSheet("color: white;");

    // Layout horizontal para os rótulos de saúde
    QHBoxLayout *healthLabelLayout = new QHBoxLayout;
    healthLabelLayout->addWidget(playerHealthLabel);
    healthLabelLayout->addStretch(); // Adiciona um espaço flexível entre os rótulos
    healthLabelLayout->addWidget(hpMessage);
    healthLabelLayout->addStretch();
    healthLabelLayout->addWidget(enemyHealthLabel);

    // Layout horizontal para os botões (lado a lado)
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(attackButton);
    buttonLayout->addWidget(potionButton);

    // Layout vertical para organizar os elementos
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(healthLabelLayout);  // Adiciona o layout dos rótulos de saúde
    mainLayout->addLayout(buttonLayout);        // Adiciona o layout dos botões

    // Configura o layout principal
    setLayout(mainLayout);

    // Inicializa a QLabel do inimigo
    enemyImgLabel = new QLabel(this);
    enemyImgLabel->setAlignment(Qt::AlignCenter);
    enemyImgLabel->hide();  // Esconde a QLabel do inimigo inicialmente

    // Layout vertical para os botões de ação (inicialmente vazio)
    actionButtonLayout = new QVBoxLayout;
    mainLayout->addLayout(actionButtonLayout);

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
    QMovie *enemyMovie = new QMovie(":/images/assets/monster/reptile/idle.gif");
    enemyImgLabel->setMovie(enemyMovie);
    enemyMovie->start();
    enemyImgLabel->setAlignment(Qt::AlignCenter);

    // Defina a geometria para ocupar a tela inteira
    enemyImgLabel->setGeometry(0, 0, width(), height());

    // Mostre a QLabel do inimigo
    enemyImgLabel->show();

    // Aumente a ordem de sobreposição para garantir que fique acima dos outros widgets
    enemyImgLabel->lower();
}

void BattleWindow::attack()
{
    // Esconde a mensagem do Hp
    hpMessage->hide();

    // Lógica para o ataque durante a batalha
    // Obtém as instâncias dos personagens do GameData
    GameData* gameData = GameData::getInstance();
    player = gameData->getPlayer();
    enemy = gameData->getEnemy();

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
    if (playerPotions > 0) {
        // Recupera 20 de saúde
        player->setHealth(player->getHealth() + 20);

        // Atualiza o número de poções e os rótulos de saúde
        playerPotions--;
        updateHealthLabels();

        // Exibe mensagem de recuperação de saúde
        QString message = QString("Você recuperou 20 de HP. Poções sobrando: %1").arg(playerPotions);
        hpMessage->setText(message);
        hpMessage->show();

        // Verifica se o jogador ainda tem poções disponíveis
        if (playerPotions == 0) {
            potionButton->setEnabled(false);  // Desativa o botão se não houver mais poções
            hpMessage->setText("Você já usou todas as poções!");
            hpMessage->show();
        }
    } else {
        hpMessage->setText("Você já usou todas as poções!");
        hpMessage->show();
    }
}

void BattleWindow::initStep()
{
    // Mostra o texto inicial e o botão de iniciar
    infoLabel->setText("Você iniciou uma batalha");
        startButton->show();

    // Esconde a QLabel do inimigo e os botões de ação
    enemyImgLabel->hide();
    attackButton->hide();
    potionButton->hide();

    // Inicializa a quantidade inicial de poções
    playerPotions = 10;
}

void BattleWindow::updateHealthLabels()
{
    // Atualiza os rótulos com informações de saúde dos personagens
    GameData* gameData = GameData::getInstance();
    Character* playerCharacter = gameData->getPlayer();
    Character* enemyCharacter = gameData->getEnemy();

    if (playerCharacter && enemyCharacter) {
        // Posiciona o rótulo de saúde do jogador
        playerHealthLabel->setText(QString("Jogador:\nSaúde: %1").arg(playerCharacter->getHealth()));

        // Posiciona o rótulo de saúde do inimigo
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
        close();            // Fecha a janela de batalha
    }
}

void Character::setHealth(int newHealth) {
    health = newHealth;
}
