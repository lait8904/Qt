#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    treeWidget = new QTreeWidget(this);

    QStringList headers;
    headers << "Название" << "Описание";
    treeWidget->setHeaderLabels(headers);

    nameLineEdit = new QLineEdit(this); // Создаем поле ввода

    connect(nameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::addItem);

    QPushButton *addButton = new QPushButton("Добавить элемент", this);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addItem);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(treeWidget);
    mainLayout->addWidget(nameLineEdit); // Добавляем поле ввода в layout
    mainLayout->addWidget(addButton);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

void MainWindow::addItem() {
    QString itemName = nameLineEdit->text();
    if (!itemName.isEmpty()) {
        for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
            QTreeWidgetItem *existingItem = treeWidget->topLevelItem(i);
            if (existingItem && existingItem->text(0) == itemName) {
                QMessageBox::warning(this, "Предупреждение", "Элемент с таким именем уже существует!");
                return;
            }
        }

        QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
        item->setText(0, itemName);

        QTreeWidgetItem *transformItem = new QTreeWidgetItem(item);
        transformItem->setText(0, "transform");


        QTreeWidgetItem *positionItem = new QTreeWidgetItem(transformItem);
        positionItem->setText(0, "posiotion");
        QWidget *positionWidget = new QWidget();
        QHBoxLayout *positionLayout = new QHBoxLayout(positionWidget);
        positionWidget->setLayout(positionLayout);
        QDoubleSpinBox *xPositionSpinBox = new QDoubleSpinBox();
        QDoubleSpinBox *yPositionSpinBox = new QDoubleSpinBox();
        xPositionSpinBox->setMinimum(-100.0);
        xPositionSpinBox->setMaximum(100.0);
        yPositionSpinBox->setMinimum(-100.0);
        yPositionSpinBox->setMaximum(100.0);
        positionLayout->addWidget(xPositionSpinBox);
        positionLayout->addWidget(yPositionSpinBox);
        positionLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget->setItemWidget(positionItem, 1, positionWidget);


        QTreeWidgetItem *rotationItem = new QTreeWidgetItem(transformItem);
        rotationItem->setText(0, "rotation");
        QWidget *rotationWidget = new QWidget();
        QDoubleSpinBox *rotationSpinBox = new QDoubleSpinBox();
        rotationSpinBox->setMinimum(-180.);
        rotationSpinBox->setMaximum(180.);
        QHBoxLayout *rotationLayout = new QHBoxLayout(rotationWidget);
        rotationLayout->addWidget(rotationSpinBox);
        rotationLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget->setItemWidget(rotationItem, 1, rotationWidget);

        QTreeWidgetItem *scaleItem = new QTreeWidgetItem(transformItem);
        scaleItem->setText(0, "scale");
        QWidget *scaleWidget = new QWidget();
        QHBoxLayout *scaleLayout = new QHBoxLayout(scaleWidget);
        scaleWidget->setLayout(scaleLayout);
        QDoubleSpinBox *xScaleSpinBox = new QDoubleSpinBox();
        QDoubleSpinBox *yScaleSpinBox = new QDoubleSpinBox();
        xScaleSpinBox->setMinimum(-100.0);
        xScaleSpinBox->setMaximum(100.0);
        yScaleSpinBox->setMinimum(-100.0);
        yScaleSpinBox->setMaximum(100.0);
        scaleLayout->addWidget(xScaleSpinBox);
        scaleLayout->addWidget(yScaleSpinBox);
        scaleLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget->setItemWidget(scaleItem, 1, scaleWidget);


        QTreeWidgetItem *parameterItem = new QTreeWidgetItem(item);
        parameterItem->setText(0, "parameter");
        QWidget *parameterWidget = new QWidget();
        QDoubleSpinBox *parameterSpinBox = new QDoubleSpinBox();
        parameterSpinBox->setMinimum(-100.);
        parameterSpinBox->setMaximum(100.0);
        QHBoxLayout *parameterLayout = new QHBoxLayout(parameterWidget);
        parameterLayout->addWidget(parameterSpinBox);
        parameterLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget->setItemWidget(parameterItem, 1, parameterWidget);

        // Очищаем поле ввода после добавления элемента
        nameLineEdit->clear();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
