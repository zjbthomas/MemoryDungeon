#include "messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QWidget *parent, string msg, string title, bool useAnimated, User* user) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->setFixedSize(539, 393);

    ui->titleLbl->setText(QString::fromStdString(title));
    ui->msgTB->setText(QString::fromStdString(msg));

    this->user = user;

    this->useAnimated = useAnimated;

    // a label with animation
    this->animatedLbl = new ClickableLabel(this, -1);
    this->animatedLbl->setGeometry(ui->imgLbl->geometry());
    this->animatedLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->okBtn->setEnabled(!useAnimated);

    ui->imgLbl->setVisible(!useAnimated);
    this->animatedLbl->setVisible(useAnimated);

    this->x = 0;
    this->cycle = 1;

    this->timer = new QTimer(this);

    this->repaintLbl(); // this requires timer, put it after timer initialization

    connect(this->animatedLbl, &ClickableLabel::released, this, [=]() {
        if (!this->timer->isActive()) {
            this->x = 0;
            this->cycle = 1;

            int kind = 0;
            this->isNewKind = this->user->gachaK(&kind);
            this->gachaPath = ":/images/cards/" + to_string(kind) + ".gif";

            this->timer->start(10);
        }
    });

    connect(this->timer, &QTimer::timeout, this, [=]() {
        this->repaintLbl();
    });

    connect(ui->okBtn, &QPushButton::released, this, [=]() {
        this->close();
    });
}

MessageDialog::~MessageDialog()
{
    delete this->animatedLbl;
    delete this->timer;

    delete ui;
}

void MessageDialog::repaintLbl() {
    QPixmap pixmap = QPixmap(":/images/cards/p.png");

    int w = this->animatedLbl->width();
    int h = this->animatedLbl->height();

    if (!this->timer->isActive()) {
        this->animatedLbl->setPixmap(pixmap.scaled(w - 2 * this->x, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        return;
    }

    if (this->x < w / 2) {
        this->animatedLbl->setPixmap(pixmap.scaled(w - 2 * this->x, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        this->x += 20;
    } else if (this->x < w) {
        if (this->cycle == 7) {
            QPixmap tempPixmap = QPixmap(QString::fromStdString(gachaPath));
            this->animatedLbl->setPixmap(tempPixmap.scaled(w - 2 * this->x, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).transformed(QTransform().scale(-1,1)));
            this->x += 20;
        } else {
            this->animatedLbl->setPixmap(pixmap.scaled(w - 2 * this->x, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).transformed(QTransform().scale(-1,1)));
            this->x += 20;
        }
    } else {
        if (this->cycle == 7) {
            this->timer->stop();

            QMovie* movie = new QMovie(QString::fromStdString(gachaPath));
            this->animatedLbl->setMovie(movie);
            movie->setScaledSize(QSize(w, h));
            movie->start();

            if (this->isNewKind) {
                ui->msgTB->setText("You find part of your memory!");
            } else {
                ui->msgTB->setText("Sorry, you are not lucky enough this time.");
            }

            ui->okBtn->setEnabled(true);

        } else {
            this->animatedLbl->setPixmap(pixmap.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

            this->cycle ++;
            this->x = 0;

            this->timer->setInterval(this->timer->interval() + 10);
        }
    }

}

void MessageDialog::showEvent(QShowEvent *e)
{
    QRect parentRect( parentWidget()->mapToGlobal( QPoint( 0, 0 ) ),
                     parentWidget()->size() );
    move( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, size(),
                             parentRect ).topLeft() );
}

void MessageDialog::keyPressEvent(QKeyEvent *e)
{
    if (e -> key() == Qt::Key_Escape ||
        e ->key() == Qt::Key_Enter ||
        e->key() == Qt::Key_Return) {
        return;
    }

    QDialog::keyPressEvent(e);
}
