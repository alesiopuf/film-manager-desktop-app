//
// Created by user on 5/30/2024.
//

#ifndef POO_LAB_10_11_MYLISTMODEL_H
#define POO_LAB_10_11_MYLISTMODEL_H

#include <QAbstractListModel>
#include <qstringlist.h>

class MyListModel : public QAbstractListModel
{
private:
    QStringList items;
public:
    MyListModel(const QStringList& Items) : items{ Items } { }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return items.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= items.size())
            return QVariant();

        if (role == Qt::DisplayRole)
            return items.at(index.row());

        return QVariant();
    }
};

#endif //POO_LAB_10_11_MYLISTMODEL_H
