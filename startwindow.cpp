#include "startwindow.h"
#include "characterselectionwindow.h"
#include "battlewindow.h"  // Adiciona o include para a tela de batalha
#include <QVBoxLayout>

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
{
    // Configuração da imagem de fundo
    QPixmap backgroundImage(":/images/assets/backgrounds/2.png");

    // Configuração do tamanho da tela
    setFixedSize(640, 480);

    // Configuração da imagem de fundo
    QPalette palette;
    palette.setBrush(backgroundRole(), backgroundImage);
    setPalette(palette);

    // Adiciona a imagem do logo na parte superior
    QLabel *logoLabel = new QLabel;
    QPixmap logoImage(":/images/assets/logo.png");
    logoLabel->setPixmap(logoImage.scaledToHeight(150));  // Ajuste conforme necessário
    logoLabel->setAlignment(Qt::AlignCenter);

    // Botões "Iniciar" e "Sair"
    QPushButton *startButton = new QPushButton("Iniciar", this);
    QPushButton *quitButton = new QPushButton("Sair", this);

    connect(startButton, &QPushButton::clicked, this, &StartWindow::startButtonClicked);
    connect(quitButton, &QPushButton::clicked, this, &StartWindow::quitButtonClicked);

    // Test Remover Após Mesclar Telas ***
    // Adiciona o botão "Batalha"
    QPushButton *battleButton = new QPushButton("Batalha", this);
    connect(battleButton, &QPushButton::clicked, this, &StartWindow::battleButtonClicked);

    // Adiciona o botão "Selecionar Personagem"
    QPushButton *selectCharacterButton = new QPushButton("Selecionar Personagem", this);
    connect(selectCharacterButton, &QPushButton::clicked, this, &StartWindow::selectCharacterButtonClicked);

    // Layout vertical para organizar os elementos
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Adiciona a imagem do logo à parte superior
    mainLayout->addWidget(logoLabel);

    // Cria um layout horizontal para os botões
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Adiciona os botões ao layout horizontal
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addWidget(selectCharacterButton);

    // Adiciona o layout horizontal de botões ao layout principal
    mainLayout->addLayout(buttonLayout);

    // Test Remover Após Mesclar Telas ***
    buttonLayout->addWidget(battleButton);  // Adiciona o botão "Batalha"

    // Configura o layout principal para a tela inicial
    setLayout(mainLayout);
}
