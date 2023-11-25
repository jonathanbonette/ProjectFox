#include "dialogwindow.h"
#include "gamedata.h"
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

    // Layout horizontal para os botões (lado a lado)
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);

    // Inicializa a QLabel do inimigo
    enemyImgLabel = new QLabel(this);
    enemyImgLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(enemyImgLabel);

    // Layout vertical para organizar o rótulo e os botões
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(enemyImgLabel);
    layout->addSpacing(40);
    layout->addLayout(buttonLayout);

    // Widget central
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Criação da árvore de diálogo
    currentNode = new DialogNode("Você está na tela inicial. Escolha um caminho:");
    DialogNode* nodeLeft = new DialogNode("(1)");
    DialogNode* nodeRight = new DialogNode("(2)");

    // Adicionando mais três telas de escolhas
    DialogNode* nodeLeftLeft = new DialogNode("(3)");
    DialogNode* nodeLeftRight = new DialogNode("(4)");
    DialogNode* nodeRightLeft = new DialogNode("(5)");
    DialogNode* nodeRightRight = new DialogNode("(6)");
    DialogNode* nodeLeftLeftLeft = new DialogNode("(7)");
    DialogNode* nodeLeftLeftRight = new DialogNode("(8)");
    DialogNode* nodeLeftRightLeft = new DialogNode("(9)");
    DialogNode* nodeLeftRightRight = new DialogNode("(10)");
    DialogNode* nodeRightLeftLeft = new DialogNode("(11)");
    DialogNode* nodeRightLeftRight = new DialogNode("(12).");
    DialogNode* nodeRightRightLeft = new DialogNode("(13)");
    DialogNode* nodeRightRightRight = new DialogNode("(14)");

    currentNode->setLeftChild(nodeLeft);
    currentNode->setRightChild(nodeRight);

    // Configura as relações entre os nós
    nodeLeft->setLeftChild(nodeLeftLeft);
    nodeLeft->setRightChild(nodeLeftRight);
    nodeRight->setLeftChild(nodeRightLeft);
    nodeRight->setRightChild(nodeRightRight);
    nodeLeftLeft->setLeftChild(nodeLeftLeftLeft);
    nodeLeftLeft->setRightChild(nodeLeftLeftRight);
    nodeLeftRight->setLeftChild(nodeLeftRightLeft);
    nodeLeftRight->setRightChild(nodeLeftRightRight);
    nodeRightLeft->setLeftChild(nodeRightLeftLeft);
    nodeRightLeft->setRightChild(nodeRightLeftRight);
    nodeRightRight->setLeftChild(nodeRightRightLeft);
    nodeRightRight->setRightChild(nodeRightRightRight);

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

        // Test 1 ***
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
                label->setText("Você, " + player->getName() + ", fez uma escolha final.");
            }
        }
    }
}

void DialogWindow::handleSpecialNode()
{
    qDebug() << "handleSpecialNode called for node:" << currentNode->getText();

    if (currentNode->getText() == "(2)") {
        // Background da tela
        QPixmap backgroundImage(":/images/assets/backgrounds/17.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        // Adiciona a imagem animada do inimigo
        QMovie *enemyMovie = new QMovie(":/images/assets/char/mage/idle.gif");
        enemyImgLabel->setMovie(enemyMovie);
        // enemyMovie->setScaledSize(QSize(303,270));
        enemyMovie->start();

        enemyImgLabel->setAlignment(Qt::AlignCenter);

        // Mostre a QLabel do inimigo
        enemyImgLabel->show();

        // Aumente a ordem de sobreposição para garantir que fique acima dos outros widgets
        enemyImgLabel->lower();

        label->setText("Você se depara com um aventureiro no caminho.\nEle olha fixamente para a esquerda, como se estivesse\nse preparando para algo de extrema importância.\n\nVocê decide ir para a Esquerda onde o aventureiro está olhando\nou segue seu caminho para a Direita?\nAliás, não é da tua conta o que ele está olhando.");
        label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        // label->setStyleSheet("color: white;");
        label->show();
    }

    if (currentNode->getText() == "(11)") {

        QPixmap backgroundImage(":/images/assets/backgrounds/22.png");
        QPalette palette;
        palette.setBrush(backgroundRole(), backgroundImage);
        setPalette(palette);

        enemyImgLabel->hide();
    }
}

