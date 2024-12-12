#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createPushButton_clicked()
{
    count = ui->countLineEdit->text().toInt();
    leftBound = ui->leftLineEdit->text().toInt();
    rightBound = ui->rightLineEdit->text().toInt();

    qDebug() << "Колличество " << count;
    qDebug() << "Левая граница " << leftBound;
    qDebug() << "Правая граница " << rightBound;

    if (leftBound > rightBound) {
        qDebug() << "Ошибка: левая граница больше правой!";
        return;
    }
    numbers.clear();
    ui->unsortTableWidget->setRowCount(0);
    ui->unsortTableWidget->verticalHeader()->setVisible(false);
    ui->unsortTableWidget->setRowCount(count);

    for (int i = 0; i < count; ++i) {
        int randomNumber = QRandomGenerator::global()->bounded(leftBound, rightBound + 1);
        numbers.append(randomNumber);

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(randomNumber));
        ui->unsortTableWidget->setItem(i, 0, item);
    }

}


void MainWindow::on_clearPushButton_clicked()
{
    numbers.clear();
    ui->unsortTableWidget->setRowCount(0);
    ui->sortTableWidget->setRowCount(0);
}


void MainWindow::on_sortPushButton_clicked()
{
    bubbleSort();
    ui->sortTableWidget->setRowCount(0);
    ui->sortTableWidget->verticalHeader()->setVisible(false);
    ui->sortTableWidget->setRowCount(count);

    for (int i = 0; i < count; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(numbers[i]));
        ui->sortTableWidget->setItem(i, 0, item);
    }
}


void MainWindow::bubbleSort()
{
    for (int i = 0; i < numbers.size() - 1; ++i) {
        for (int j = 0; j < numbers.size() - i - 1; ++j) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}
