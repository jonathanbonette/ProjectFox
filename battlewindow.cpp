#include "battlewindow.h"
#include "gamedata.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMovie>
#include <QDebug>

BattleWindow::BattleWindow(QWidget *parent, const QString &enemyType)
    : QWidget(parent), player(nullptr), enemy(nullptr), enemyType(enemyType)
{
    // Inicia a quantidade total das poções
    playerPotions = 20;

    // Configuração da tela de batalha
    setFixedSize(640, 480);
    QPixmap backgroundImage(":/images/assets/backgrounds/12.png");
    QPalette palette;
    palette.setBrush(backgroundRole(), backgroundImage);
    setPalette(palette);

    // Rótulo para exibir informações sobre a batalha
    infoLabel = new QLabel("Você iniciou uma batalha", this);
    infoLabel->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    infoLabel->setFont(QFont("SansSerif", 10, QFont::Bold));
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
    playerHealthLabel->setFont(QFont("SansSerif", 10, QFont::Bold));
    playerHealthLabel->setStyleSheet("color: white;");
    enemyHealthLabel->setFont(QFont("SansSerif", 10, QFont::Bold));
    enemyHealthLabel->setStyleSheet("color: white;");

    // Criação de um QLabel para exibir mensagens dinâmicas
    hpMessage = new QLabel(this);
    hpMessage->setAlignment(Qt::AlignTop);
    hpMessage->setFont(QFont("SansSerif", 10, QFont::Bold));
    hpMessage->setStyleSheet("color: white;");

    resultAttackLabel = new QLabel(this);
    resultAttackLabel->setAlignment(Qt::AlignTop);
    resultAttackLabel->setFont(QFont("SansSerif", 10, QFont::Bold));
    resultAttackLabel->setStyleSheet("color: white;");

    // Layout horizontal para os rótulos de saúde
    QHBoxLayout *healthLabelLayout = new QHBoxLayout;
    healthLabelLayout->addWidget(playerHealthLabel);
    healthLabelLayout->addStretch(); // Adiciona um espaço flexível entre os rótulos
    healthLabelLayout->addWidget(hpMessage);
    healthLabelLayout->addWidget(resultAttackLabel);
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

    // Configura o jogador no GameData
    GameData *gameData = GameData::getInstance();
    gameData->getPlayer();

    // Cria o inimigo com base no tipo especificado
    if (enemyType == "InimigoPeludo") {
        enemy = new Character("Inimigo Peludo", 80, 15, 10);
    } else if (enemyType == "GuerreiroGigante") {
        enemy = new Character("Guerreiro Gigante", 150, 20, 35);
    } else if (enemyType == "Mimico") {
        enemy = new Character("Mimico", 50, 50, 10);
    } else if (enemyType == "GrupoDeInimigos") {
        enemy = new Character("Grupo de Inimigos", 400, 50, 30);
    }

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

    // Recupera o número de poções do GameData
    playerPotions = GameData::getPlayerPotions();

    // Cria a imagemdo inimigo com base no tipo especificado
    if (enemyType == "InimigoPeludo") {

        QMovie *enemyMovie = new QMovie(":/images/assets/monster/reptile/idle.gif");
        enemyImgLabel->setMovie(enemyMovie);
        enemyMovie->start();
        enemyImgLabel->setAlignment(Qt::AlignCenter);

    } else if (enemyType == "GuerreiroGigante") {

        QMovie *enemyMovie = new QMovie(":/images/assets/monster/giant/idle.gif");
        enemyImgLabel->setMovie(enemyMovie);
        enemyMovie->start();
        enemyImgLabel->setAlignment(Qt::AlignCenter);

    } else if (enemyType == "Mimico") {

        QMovie *enemyMovie = new QMovie(":/images/assets/monster/mimic/idle.gif");
        enemyImgLabel->setMovie(enemyMovie);
        enemyMovie->start();
        enemyImgLabel->setAlignment(Qt::AlignCenter);

    } else if (enemyType == "GrupoDeInimigos") {

        QMovie *enemyMovie = new QMovie(":/images/assets/group-enemy.gif");
        enemyImgLabel->setMovie(enemyMovie);
        enemyMovie->start();
        enemyImgLabel->setAlignment(Qt::AlignCenter);
    }

    // Exibe a imagem abaixo doa botões
    enemyImgLabel->setGeometry(0, 0, width(), height());
    enemyImgLabel->show();
    enemyImgLabel->lower();
}

void BattleWindow::attack()
{
    // Esconde a mensagem do Hp
    hpMessage->hide();

    // Obtém as instâncias dos personagens do GameData
    GameData* gameData = GameData::getInstance();
    player = gameData->getPlayer();
    enemy = gameData->getEnemy();

    // Lógica para o ataque durante a batalha
    AttackResult playerResult = player->attackEnemy(*enemy);
    updateHealthLabels();  // Atualiza os rótulos de saúde

    // Exibe mensagem de resultado do ataque do jogador
    resultAttackLabel->setText(playerResult.message);
    resultAttackLabel->show();

    // Lógica para a resposta do inimigo
    if (enemy->getHealth() > 0) {
        AttackResult enemyResult = enemy->attackEnemy(*player, false);
        updateHealthLabels();  // Atualiza os rótulos de saúde após o ataque do inimigo

        // Adiciona a mensagem de resultado do ataque do inimigo ao texto existente
        resultAttackLabel->setText(resultAttackLabel->text() + "\n" + enemyResult.message);
        resultAttackLabel->show();
    }

    // Verifica se a batalha terminou
    checkBattleResult();
}

void BattleWindow::usePotion()
{
    GameData* gameData = GameData::getInstance();
    player = gameData->getPlayer();

    resultAttackLabel->hide();

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

        // Atualiza o número de poções no GameData
        GameData::setPlayerPotions(playerPotions);

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

        // Emite o sinal indicando que a batalha terminou
        emit battleFinished();

        // Fecha a janela de batalha
        close();
    }
}

void Character::setHealth(int newHealth) {
    // Método da classe Character para configurar a saúde após o uso da potion
    health = newHealth;
}
