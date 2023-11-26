// dialoghelper.h

#ifndef DIALOGHELPER_H
#define DIALOGHELPER_H

#include <QString>

class DialogHelper
{
public:
    static void updateBackground(class DialogWindow *window, const QString &imagePath);
    static void updateLabel(class DialogWindow *window, const QString &text, Qt::Alignment alignment, const QString &styleSheet);
    static void showAcceptGiftButton(class DialogWindow *window);
    static void hideChoiceButtons(class DialogWindow *window);
    static void showChoiceButtons(class DialogWindow *window);
    static void updateMovieImage(DialogWindow *window, const QString &moviePath);
    static void updateImageLabel(DialogWindow *window, const QString &imagePngPath);

    // ... outras funções auxiliares conforme necessário
};

#endif // DIALOGHELPER_H
