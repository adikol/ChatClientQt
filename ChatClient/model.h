#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QStringList>

class Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0){}
    explicit Model(QStringList list ,QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    virtual QModelIndex parent(const QModelIndex & index ) const;
    Q_INVOKABLE virtual int rowCount( const QModelIndex & parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const;
    Q_INVOKABLE bool insertRows(int position, int rows, const QModelIndex &index);


    Q_INVOKABLE QString returnSubmodelForData(int index)
    {
        return m_usernames.at(index);
    }




signals:
    
public slots:

private:
    QList<QString> m_usernames;
    QStringList m_rosterlist;
};

#endif // MODEL_H
