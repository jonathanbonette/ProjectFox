#include <QApplication>
#include "startwindow.h"
#include "characterselectionwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartWindow startWindow;

    // Quando o botão "Selecionar Personagem" é clicado, exibe a janela de seleção de personagens
    QObject::connect(&startWindow, &StartWindow::selectCharacterButtonClicked, [&]() {
        startWindow.hide();  // Esconde a tela inicial

        // Exibe a janela de seleção de personagens
        startWindow.characterSelectionWindow.show();
    });

    // Quando o botão "Sair" é clicado, fecha o aplicativo
    QObject::connect(&startWindow, &StartWindow::quitButtonClicked, &a, &QApplication::quit);

    // Exibe a tela inicial
    startWindow.show();

    // Inicia o loop de eventos do Qt
    return a.exec();
}
