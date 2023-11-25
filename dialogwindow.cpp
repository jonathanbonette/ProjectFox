#include "dialogwindow.h"
#include "battlewindow.h"
#include "gamedata.h"
#include "battlewindow.h"
#include <QMovie>

DialogWindow::DialogWindow(QWidget *parent)
    : QMainWindow(parent), currentNode(nullptr)
{
    createWidgets();
}

DialogWindow::~DialogWindow() { delete currentNode; }

// Implementações dos métodos da classe DialogWindow

void DialogWindow::createWidgets()
{
    label = new QLabel(this);

    // Exibe a janela de diálogo
    setFixedSize(640, 480);
    QPixmap backgroundImage(":/images/assets/backgrounds/1.png");
    QPalette palette;
    palette.setBrush(backgroundRole(), backgroundImage);
    setPalette(palette);

    // Configurações visuais para o rótulo
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("System", 36, QFont::Bold));

    leftButton = new QPushButton("Esquerda", this);
    rightButton = new QPushButton("Direita", this);

    // Conecta os botões ao slot handleChoice
    connect(leftButton, &QPushButton::clicked, this, &DialogWindow::handleChoice);
    connect(rightButton, &QPushButton::clicked, this, &DialogWindow::handleChoice);

    // Adiciona o botão "Aceitar o presente"
    acceptGiftButton = new QPushButton("Aceitar o presente", this);
    connect(acceptGiftButton, &QPushButton::clicked, this, &DialogWindow::handleAcceptGift);
    QHBoxLayout *acceptGiftButtonLayout = new QHBoxLayout;
    // Adicione o botão à layout
    acceptGiftButtonLayout->addWidget(acceptGiftButton);
    acceptGiftButton->hide();

    // Layout horizontal para os botões (lado a lado)
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);
    buttonLayout->addWidget(acceptGiftButton);

    // Inicializa a QLabel do inimigo
    npcImgLabel = new QLabel(this);
    npcImgLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(npcImgLabel);

    // Layout vertical para organizar o rótulo e os botões
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(npcImgLabel);
    layout->addSpacing(40);
    layout->addLayout(buttonLayout);

    // Widget central
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Criação da árvore de diálogo
    currentNode = new DialogNode("Em uma distante e enigmática terra, você inicia uma jornada repleta de escolhas.\nDiante de vários caminhos bifurcados sua aventura começa.\nCada decisão moldará seu destino, revelando segredos, enfrentando desafios\ne forjando uma história única.\nQual rumo você escolherá nesta trama repleta de mistérios e magia?\n\nPara começar, qual é sua primeira escolha dessa jornada?\n\nVocê decide:","Checar a clareira","Investigar os sons do cânion");
    DialogNode* nodeLeft = new DialogNode("(1)", "Interagir com as criaturas místicas", "Investigar a fonte mágica");
    DialogNode* nodeRight = new DialogNode("(2)");

    // Adicionando mais três telas de escolhas
    DialogNode* nodeLeftLeft = new DialogNode("(3)","Seguir caminho");
    DialogNode* nodeLeftRight = new DialogNode("(4)");
    DialogNode* nodeRightLeft = new DialogNode("(5)");
    DialogNode* nodeRightRight = new DialogNode("(6)");
    DialogNode* nodeLeftLeftLeft = new DialogNode("(7)");
    //DialogNode* nodeLeftLeftRight = new DialogNode("(8)");
    DialogNode* nodeLeftRightLeft = new DialogNode("(9)");
    DialogNode* nodeLeftRightRight = new DialogNode("(10)");
    DialogNode* nodeRightLeftLeft = new DialogNode("(11)");
    DialogNode* nodeRightLeftRight = new DialogNode("(12).");
    DialogNode* nodeRightRightLeft = new DialogNode("(13)");
    DialogNode* nodeRightRightRight = new DialogNode("(14)");

    // Adicione dois novos nós
    // DialogNode* nodeRightRightLeftLeft = new DialogNode("(15)");
    DialogNode* nodeRightRightLeftRight = new DialogNode("(16)");

    DialogNode* nodeLeftRightLeftLeft = new DialogNode("(17)");
    DialogNode* nodeLeftRightLeftRight = new DialogNode("(18)");

    currentNode->setLeftChild(nodeLeft);
    currentNode->setRightChild(nodeRight);

    // Configura as relações entre os nós
    nodeLeft->setLeftChild(nodeLeftLeft);
    nodeLeft->setRightChild(nodeLeftRight);
    nodeRight->setLeftChild(nodeRightLeft);
    nodeRight->setRightChild(nodeRightRight);
    nodeLeftLeft->setLeftChild(nodeLeftLeftLeft);
    //nodeLeftLeft->setRightChild(nodeLeftLeftRight);
    nodeLeftRight->setLeftChild(nodeLeftRightLeft);
    nodeLeftRight->setRightChild(nodeLeftRightRight);
    nodeRightLeft->setLeftChild(nodeRightLeftLeft);
    nodeRightLeft->setRightChild(nodeRightLeftRight);
    nodeRightRight->setLeftChild(nodeRightRightLeft);
    nodeRightRight->setRightChild(nodeRightRightRight);

    // Configure as relações entre os novos nós e o nó existente (14)
    // nodeRightRightLeft->setLeftChild(nodeRightRightLeftLeft);
    nodeRightRightLeft->setRightChild(nodeRightRightLeftRight);

    // Atualiza os textos dos botões com base no nó atual
    leftButton->setText(currentNode->getLeftButtonText());
    rightButton->setText(currentNode->getRightButtonText());

    // Define o texto inicial no rótulo
    label->setText(currentNode->getText());
}

void DialogWindow::handleChoice()
{
    if (currentNode) {
        // Verifica qual botão foi clicado
        QPushButton *button = qobject_cast<QPushButton*>(sender());

        // Atualiza o nó atual com base na escolha do usuário
        if (button == leftButton && currentNode->getLeftChild()) {
            currentNode = currentNode->getLeftChild();
        } else if (button == rightButton && currentNode->getRightChild()) {
            currentNode = currentNode->getRightChild();
        }

        // Atualiza o texto exibido no rótulo
        label->setText(currentNode->getText());

        // Atualiza os textos dos botões com base no nó atual
        leftButton->setText(currentNode->getLeftButtonText());
        rightButton->setText(currentNode->getRightButtonText());

        handleSpecialNode();

        // Desativa os botões se não houver mais escolhas
        if (!currentNode->getLeftChild() && !currentNode->getRightChild()) {
            leftButton->setEnabled(false);
            rightButton->setEnabled(false);

            // Verifica se há um jogador definido no GameData
            GameData *gameData = GameData::getInstance();
            Character* player = gameData->getPlayer();
            if (player) {
                // Usa as informações do jogador na história
                label->setText("Você, " + player->getName() + ", chegou ao final dessa pequena grande história.\nMeus parabéns, outras grandes aventuras estão por vir!");
            }
        } else {
            // Desabilita o botão direito se estiver no nó correspondente à tela (3)
            rightButton->setEnabled(currentNode->getText() != "(3)");
            leftButton->setEnabled(currentNode->getText() != "(13)");
        }
    }
}

void DialogWindow::handleSpecialNode()
{
    // qDebug() << "handleSpecialNode called for node:" << currentNode->getText();

    //------------------------------------------------------------------

    if (currentNode->getText() == "(1)") {

        QPixmap backgroundImage(":/images/assets/backgrounds/11.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        label->setText("Ao optar por explorar a clareira, você se aventura por entre as árvores densas da floresta,\nguiado pelo suave murmúrio do vento e pela luz que começa a penetrar as copas das árvores.\nÀ medida que avança, um cenário mágico se revela diante dos seus olhos.\nVocê continua andando e conforme explora a clareira,\npercebe indícios de uma presença mágica.\nFlores que brilham sutilmente, pequenos seres místicos que se escondem entre as folhagens\ne um sentimento de ser observado por algo além do alcance dos olhos.\n\nNesse ponto, suas escolhas ganham um novo significado.\n\nVocê decide:");
        label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        label->setStyleSheet("color: white;");
        label->show();
    }

    //------------------------------------------------------------------

    if (currentNode->getText() == "(3)") {
        // Background da tela
        QPixmap backgroundImage(":/images/assets/backgrounds/12.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        // Adiciona a imagem animada do inimigo
        QMovie *npcMageMovie = new QMovie(":/images/assets/monster/ghost/idle.gif");
        npcImgLabel->setMovie(npcMageMovie);
        npcMageMovie->start();

        npcImgLabel->setAlignment(Qt::AlignCenter);

        // Mostre a QLabel do inimigo
        npcImgLabel->show();
        npcImgLabel->lower();

        leftButton->hide();
        rightButton->hide();
        acceptGiftButton->show();

        label->setText("Ao escolher interagir com as criaturas místicas, o ambiente na clareira\npassa por uma transformação abrupta, com a luz diminuindo e sombras envolvendo o local.\nUma das criaturas, inicialmente imponente, se aproxima lentamente, seu único olho brilhando\ncom uma luz suave que inicialmente causa apreensão.\nContudo, ao se aproximar, a criatura revela-se amigável,\nestendendo uma pequena mão e oferecendo um presente.");
        label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        label->setStyleSheet("color: white;");
        label->show();
    }

    //------------------------------------------------------------------

    if (currentNode->getText() == "(7)") {

        QPixmap backgroundImage(":/images/assets/backgrounds/11.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        npcImgLabel->hide();
        leftButton->hide();
        rightButton->hide();

    }

    //------------------------------------------------------------------


    if (currentNode->getText() == "(2)") {
        // Background da tela
        QPixmap backgroundImage(":/images/assets/backgrounds/17.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        // Adiciona a imagem animada do inimigo
        QMovie *npcMageMovie = new QMovie(":/images/assets/char/mage/idle.gif");
        npcImgLabel->setMovie(npcMageMovie);
        // enemyMovie->setScaledSize(QSize(303,270));
        npcMageMovie->start();

        npcImgLabel->setAlignment(Qt::AlignCenter);

        // Mostre a QLabel do inimigo
        npcImgLabel->show();
        npcImgLabel->lower();

        label->setText("Você se depara com um aventureiro no caminho.\nEle olha fixamente para a esquerda, como se estivesse\nse preparando para algo de extrema importância.\n\nVocê decide ir para a Esquerda onde o aventureiro está olhando\nou segue seu caminho para a Direita?");
        label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        // label->setStyleSheet("color: white;");
        label->show();
    }

    //------------------------------------------------------------------

    if (currentNode->getText() == "(5)") {

        QPixmap backgroundImage(":/images/assets/backgrounds/22.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        npcImgLabel->hide();

        // Cria uma tela de batalha
        BattleWindow* battleWindow = new BattleWindow(this, "GuerreiroGigante");

        leftButton->hide();
        rightButton->hide();
        label->hide();

        battleWindow->show();

        // Verifica se a batalha terminou (saúde de jogador ou inimigo <= 0)
        GameData* gameData = GameData::getInstance();
        Character* playerCharacter = gameData->getPlayer();

        connect(battleWindow, &BattleWindow::battleFinished, this, [=]() {
            // Verifica se o jogador foi derrotado
            if (playerCharacter->getHealth() <= 0) {

                // Exibe o texto informando que a jornada terminou
                label->setText("Sua jornada terminou...");
                label->show();

                // Esconde os botões de escolha
                leftButton->hide();
                rightButton->hide();
            }

            label->show();
            leftButton->show();
            rightButton->show();
        });

    }

    //------------------------------------------------------------------

    if (currentNode->getText() == "(11)") {

        QPixmap backgroundImage(":/images/assets/backgrounds/22.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        npcImgLabel->hide();
    }

    //------------------------------------------------------------------
}


void DialogWindow::handleAcceptGift()
{
    label->setText("Aceitando o presente, percebe-se que as criaturas não eram ameaçadoras,\nmas sim guardiãs da floresta.\nElas compartilham contigo um livro que contém informações grandiosas.\nAgradecendo, a criaturas que veio ao teu encontro desaparece nas sombras,\ndeixando para trás apenas o item dado a você.");
    label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label->setStyleSheet("color: white;");
    label->show();

    acceptGiftButton->hide();
    leftButton->show();
    rightButton->show();

    // Adiciona um item na telas
    QPixmap itemImage(":/images/assets/item/41.png");
    npcImgLabel->setPixmap(itemImage);
    npcImgLabel->setAlignment(Qt::AlignCenter);

    // Mostre a QLabel do inimigo
    npcImgLabel->show();

    // Aumente a ordem de sobreposição para garantir que fique acima dos outros widgets
    npcImgLabel->lower();
}
