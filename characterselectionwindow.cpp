#include "characterselectionwindow.h"
#include "character.h"
#include "gamedata.h"
#include "qlabel.h"
#include <QVBoxLayout>

CharacterSelectionWindow::CharacterSelectionWindow(QWidget *parent)
    : QWidget(parent)
{
    // Inicializa a criação dos widgets da tela de seleção de personagens
    createWidgets();
}

void CharacterSelectionWindow::createWidgets()
{
    // Configuração da imagem de fundo
    QPixmap backgroundImage(":/images/assets/backgrounds/7.png");

    // Configuração da imagem de fundo
    QPalette palette;
    palette.setBrush(backgroundRole(), backgroundImage);
    setPalette(palette);

    // Configuração do tamanho da tela
    setFixedSize(640, 480);

    // Criação dos labels para as imagens dos personagens
    QLabel *archerImg = new QLabel;
    QLabel *mageImg = new QLabel;
    QLabel *warriorImg = new QLabel;
    QLabel *paladinImg = new QLabel;

    // Configuração das imagens para os labels dos personagens
    archerImg->setPixmap(QPixmap(":/images/assets/char/g_archer.png"));
    mageImg->setPixmap(QPixmap(":/images/assets/char/g_mage.png"));
    warriorImg->setPixmap(QPixmap(":/images/assets/char/g_warrior.png"));
    paladinImg->setPixmap(QPixmap(":/images/assets/char/g_paladin.png"));

    // Ajuste de alinhamento dos labels
    archerImg->setAlignment(Qt::AlignCenter);
    mageImg->setAlignment(Qt::AlignCenter);
    warriorImg->setAlignment(Qt::AlignCenter);
    paladinImg->setAlignment(Qt::AlignCenter);

    // Criação dos botões para seleção dos personagens
    QPushButton *archerButton = new QPushButton("Arqueiro", this);
    QPushButton *wizardButton = new QPushButton("Mago", this);
    QPushButton *warriorButton = new QPushButton("Guerreiro", this);
    QPushButton *paladinButton = new QPushButton("Paladino", this);

    // Conexão dos botões aos slots correspondentes
    connect(archerButton, &QPushButton::clicked, this, [=]() { characterSelected(new Archer()); });
    connect(wizardButton, &QPushButton::clicked, this, [=]() { characterSelected(new Mage()); });
    connect(warriorButton, &QPushButton::clicked, this, [=]() { characterSelected(new Warrior()); });
    connect(paladinButton, &QPushButton::clicked, this, [=]() { characterSelected(new Paladin()); });

    // Layout vertical para organizar os elementos
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Cria um layout horizontal para os personagens
    QHBoxLayout *charactersLayout = new QHBoxLayout;

    // Adiciona as imagens dos personagems na tela
    charactersLayout->addWidget(archerImg);
    charactersLayout->addWidget(mageImg);
    charactersLayout->addWidget(warriorImg);
    charactersLayout->addWidget(paladinImg);

    mainLayout->addLayout(charactersLayout);

    // Cria um layout horizontal para os botões
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Adiciona os botões de seleção ao layout dos botões
    buttonLayout->addWidget(archerButton);
    buttonLayout->addWidget(wizardButton);
    buttonLayout->addWidget(warriorButton);
    buttonLayout->addWidget(paladinButton);

    // Adiciona o layout horizontal de botões ao layout principal
    mainLayout->addLayout(buttonLayout);

    // Configura o layout principal para a tela de seleção de personagens
    setLayout(mainLayout);
}

void CharacterSelectionWindow::characterSelected(Character *character)
{
    // Configurar o jogador no GameData
    GameData *gameData = GameData::getInstance();
    gameData->setPlayer(character);

    // Configurar o DialogWindow no GameData
    DialogWindow* dialogWindow = new DialogWindow;
    gameData->setDialogWindow(dialogWindow);

//    // Exibir informações sobre o personagem selecionado
//    QMessageBox::information(this, "Personagem Selecionado", QString(
//                                                                 "Você selecionou o personagem: %1 \nVida: %2 \nAtaque: %3 \nDefesa: %4")
//                                                                     .arg(character->getName())
//                                                                     .arg(character->getHealth())
//                                                                     .arg(character->getAttack())
//                                                                     .arg(character->getDefense())
//                                                                 );

    // Mostrar o DialogWindow
    dialogWindow->show();
    this->close();          // Fecha a janela de seleção de personagem
}
