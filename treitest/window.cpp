#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    //const auto iconSize = QSize(100, 100);
    //auto mainBox = new QVBoxLayout();
    //auto bottomBox  = new QHBoxLayout();
    //auto clearBtn  = new QPushButton("clear");
    //auto selectBtn = new QPushButton("select");

    //auto view = new QListWidget();
    //view->setIconSize(iconSize);
    //view->setViewMode(QListView::IconMode);
    //view->setResizeMode(QListView::ResizeMode::Adjust);

    //connect(clearBtn, &QPushButton::clicked, view, &QListWidget::clear);

    //connect(selectBtn, &QPushButton::clicked, [view, iconSize]() -> void
    //        {
    //            QStringList files = QFileDialog::getOpenFileNames(0,"","","*.png *.jpg");
    //            for(auto& file : files)
    //            {
    //                auto item = new QListWidgetItem("", view);
    //                auto image = QPixmap(file).scaled(iconSize, Qt::AspectRatioMode::KeepAspectRatio);
    //                item->setIcon(image);
    //            }
    //        });

    //bottomBox->addWidget(clearBtn, 0, Qt::AlignLeft);
    //bottomBox->addWidget(selectBtn, 0, Qt::AlignRight);

    //mainBox->addWidget(view);
    //mainBox->addLayout(bottomBox);
    //setLayout(mainBox);
}

Window::~Window()
{

}


void Window::paintEvent(QPaintEvent *) {
    QPainterPath path;       // создаем путь
    path.moveTo(115, 10);
    path.lineTo(230, 140);
    path.lineTo(10, 140);
    path.closeSubpath();

    QPainter painter(this);

    painter.fillPath(path, QBrush{"#2980b9"});  // окрашиваем путь

    //trianglePath = path;
}

//void Window::mousePressEvent(QMouseEvent *event) {
//    if (trianglePath.contains(event->pos())) {
//        qDebug() << "Клик внутри треугольника!";
//    } else {
//        qDebug() << "Клик вне треугольника.";
//    }
//}
