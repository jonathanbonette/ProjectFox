#ifndef DIALOGHELPER_H
#define DIALOGHELPER_H

#include <QString>

class DialogHelper
{
public:
    // Métodos para genericalizar as chamadas das telas
    static void updateBackground(class DialogWindow *window, const QString &imagePath);
    static void updateLabel(class DialogWindow *window, const QString &text, Qt::Alignment alignment, const QString &styleSheet);
    static void showAcceptGiftButton(class DialogWindow *window);
    static void hideChoiceButtons(class DialogWindow *window);
    static void showChoiceButtons(class DialogWindow *window);
    static void updateMovieImage(DialogWindow *window, const QString &moviePath);
    static void updateImageLabel(DialogWindow *window, const QString &imagePngPath);
};

#endif // DIALOGHELPER_H
