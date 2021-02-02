#include "model.h"
#include <qDebug>
#include <iostream>
using namespace std;

Model::Model(QStringList list,QObject *parent) :
    QAbstractItemModel(parent)
{
    m_rosterlist = list;

    insertRows(0,m_rosterlist.count(),QModelIndex());
}

bool Model::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; row++) {
        m_usernames.insert(position, m_rosterlist.at(position));
       position++;
    }   

    endInsertRows();
    return true;
}

QModelIndex Model::index(int row, int column, const QModelIndex & parent ) const
{
 // To be implemented
}

QModelIndex Model::parent(const QModelIndex & index) const
{
    // To be implemented
}

int Model::rowCount(const QModelIndex & parent) const
{   
    return m_usernames.count();
}

int Model::columnCount(const QModelIndex & parent) const
{
    // To be implemented
}

QVariant Model::data(const QModelIndex & index,int role) const
{
    // To be implemented
}
