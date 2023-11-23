#include "characterselectionwindow.h"
#include "character.h"
#include "gamedata.h"
#include "qlabel.h"
#include <QVBoxLayout>

CharacterSelectionWindow::CharacterSelectionWindow(QWidget *parent)
    : QWidget(parent)
{
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

    // Adiciona a imagem do arqueiro
    QLabel *archerImg = new QLabel;
    QPixmap img1(":/images/assets/char/g_archer.png");
    archerImg->setPixmap(img1);
    archerImg->setAlignment(Qt::AlignCenter);

    // Adiciona a imagem do mago
    QLabel *mageImg = new QLabel;
    QPixmap img2(":/images/assets/char/g_mage.png");
    mageImg->setPixmap(img2);
    mageImg->setAlignment(Qt::AlignCenter);

    // Adiciona a imagem do guerreiro
    QLabel *warriorImg = new QLabel;
    QPixmap img3(":/images/assets/char/g_warrior.png");
    warriorImg->setPixmap(img3);  // Ajuste conforme necessário
    warriorImg->setAlignment(Qt::AlignCenter);

    // Adiciona a imagem do paladino
    QLabel *paladinImg = new QLabel;
    QPixmap img4(":/images/assets/char/g_paladin.png");
    paladinImg->setPixmap(img4);  // Ajuste conforme necessário
    paladinImg->setAlignment(Qt::AlignCenter);

    // Cria os botões dos personagens
    QPushButton *archerButton = new QPushButton("Arqueiro", this);
    QPushButton *wizardButton = new QPushButton("Mago", this);
    QPushButton *warriorButton = new QPushButton("Guerreiro", this);
    QPushButton *paladinButton = new QPushButton("Paladino", this);

    // Conectar os botões aos slots correspondentes
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

    buttonLayout->addWidget(archerButton);
    buttonLayout->addWidget(wizardButton);
    buttonLayout->addWidget(warriorButton);
    buttonLayout->addWidget(paladinButton);

    // Adiciona o layout horizontal de botões ao layout principal
    mainLayout->addLayout(buttonLayout);

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

    // DEBUG
    // Exibir informações sobre o personagem selecionado
    QMessageBox::information(this, "Personagem Selecionado", QString(
                                                                 "Você selecionou o personagem: %1 \nVida: %2 \nAtaque: %3 \nDefesa: %4")
                                                                     .arg(character->getName())
                                                                     .arg(character->getHealth())
                                                                     .arg(character->getAttack())
                                                                     .arg(character->getDefense())
                                                                 );

    // Mostrar o DialogWindow
    dialogWindow->show();
    this->close();  // Fechar a janela de seleção de personagem

}
