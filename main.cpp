#include <QApplication>
#include "dialogtree.h"

// Test ***
//#include "gamedata.h"

#include "startwindow.h"
#include "characterselectionwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartWindow startWindow;

    QObject::connect(&startWindow, &StartWindow::startButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de árvore de escolhas
        startWindow.dialogWindow.show();
    });

    QObject::connect(&startWindow, &StartWindow::selectCharacterButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de seleção de personagens
        startWindow.characterSelectionWindow.show();
    });

    QObject::connect(&startWindow, &StartWindow::quitButtonClicked, &a, &QApplication::quit);

    QObject::connect(&startWindow, &StartWindow::battleButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de batalha
        startWindow.battleWindow.show();
    });

    startWindow.show();

    return a.exec();
}
