#include <QApplication>
#include "dialogtree.h"
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

        // Test ***
        // Cria instâncias dos personagens (exemplo: Guerreiro e Inimigo Peludo)
        Character *player = new Character("Asgorn", 100, 20, 10);
        Character *enemy = new Character("Inimigo Peludo", 80, 15, 8);

        // Configura os personagens na janela de batalha
        startWindow.battleWindow.setCharacters(player, enemy);

        // Exibe a janela de batalha
        startWindow.battleWindow.show();
    });

    startWindow.show();

    return a.exec();
}
