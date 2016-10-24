#ifndef DIALOGANNOTATION_H
#define DIALOGANNOTATION_H

#include <iostream>
#include <string>
#include <map>
using std::string;
using std::multimap;

#include <QDialog>
#include <QModelIndex>
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>

#include "core.h"
#include "qmultimapmodel.h"

namespace Ui {
    class DialogAnnotation;
}

class DialogAnnotation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnnotation(QWidget *parent = 0);
    ~DialogAnnotation();

private:
    void connectSignalSlots();
    void enableWidgets(const bool _enable);
    void updateCoreContent();
    void updateWidgets();

private:
    Ui::DialogAnnotation *ui;
    QMultiMap<QString, QString> qAttributes;
    QStringListModel *qCategoriesModel;
    QStringListModel *qLabelsModel;

    QMultiMapModel *qMapModelTest;

    QString selectedCategory;
    QString selectedLabel;

    Core *singleton = NULL;

public slots:
    void slot_initializeDialog(Core &_singleton);

private slots:
    void slot_listViewCategoriesClicked(QModelIndex _index);
    void slot_listViewLabelsClicked(QModelIndex _index);
    void slot_listViewCategoryEntered(QModelIndex _index);
    void slot_listViewLabelEntered(QModelIndex _index);

    void slot_insertCategoryPressed();
    void slot_insertLabelPressed();
    void slot_removeCategoryPressed();
    void slot_removeLabelPressed();
};

#endif // DIALOGANNOTATION_H
