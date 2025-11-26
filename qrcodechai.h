#ifndef QRCODECHAI_H
#define QRCODECHAI_H

#include <QDialog>
#include <QPixmap>

#include "qrcodogen.h"        // ta librairie QR (Nayuki)

// ⚠️ Ce nom doit correspondre au nom de ton .ui : qrcodechai.ui → ui_qrcodechai.h
#include "ui_qrcodechai.h"

namespace Ui {
class qrcodechai;
}

class qrcodechai : public QDialog
{
    Q_OBJECT

public:
    explicit qrcodechai(QWidget *parent = nullptr);
    ~qrcodechai();

private slots:
    void on_pushButton_generate_clicked();   // bouton "Générer"

private:
    Ui::qrcodechai *ui;                      // pointeur vers l'UI générée

    QString getClientDataByID(const QString &id);  // récupérer les infos client
    QPixmap generateQRCode(const QString &data);   // générer le QR code
};

#endif // QRCODECHAI_H
