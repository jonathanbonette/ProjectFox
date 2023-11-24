#include <QApplication>
#include "dialogtree.h"
#include "startwindow.h"
#include "characterselectionwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartWindow startWindow;

    // Quando o botão "Iniciar" é clicado, exibe a janela de árvore de escolhas
    QObject::connect(&startWindow, &StartWindow::startButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de árvore de escolhas
        startWindow.dialogWindow.show();
    });

    // Quando o botão "Selecionar Personagem" é clicado, exibe a janela de seleção de personagens
    QObject::connect(&startWindow, &StartWindow::selectCharacterButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de seleção de personagens
        startWindow.characterSelectionWindow.show();
    });

    // Quando o botão "Sair" é clicado, fecha o aplicativo
    QObject::connect(&startWindow, &StartWindow::quitButtonClicked, &a, &QApplication::quit);

    // Quando o botão "Batalha" é clicado, exibe a janela de batalha
    QObject::connect(&startWindow, &StartWindow::battleButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de batalha
        startWindow.battleWindow.show();
    });

    // Exibe a tela inicial
    startWindow.show();

    // Inicia o loop de eventos do Qt
    return a.exec();
}
