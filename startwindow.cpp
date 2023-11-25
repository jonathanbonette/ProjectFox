#include "startwindow.h"
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
    logoLabel->setPixmap(logoImage.scaledToHeight(150));
    logoLabel->setAlignment(Qt::AlignCenter);

    // Botões "Selecionar Personagem" e "Sair"
    QPushButton *quitButton = new QPushButton("Sair", this);
    connect(quitButton, &QPushButton::clicked, this, &StartWindow::quitButtonClicked);

    QPushButton *selectCharacterButton = new QPushButton("Iniciar Jornada", this);
    connect(selectCharacterButton, &QPushButton::clicked, this, &StartWindow::selectCharacterButtonClicked);

    // Layout vertical para organizar os elementos
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Adiciona a imagem do logo à parte superior
    mainLayout->addWidget(logoLabel);

    // Cria um layout horizontal para os botões
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Adiciona os botões ao layout horizontal
    buttonLayout->addWidget(selectCharacterButton);
    buttonLayout->addWidget(quitButton);

    // Adiciona o layout horizontal de botões ao layout principal
    mainLayout->addLayout(buttonLayout);

    // Configura o layout principal para a tela inicial
    setLayout(mainLayout);
}
