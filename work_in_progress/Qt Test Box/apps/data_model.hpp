#ifndef DATA_MODEL_HPP
#define DATA_MODEL_HPP
#include <QAbstractTableModel>

class DataModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    unsigned int data_;

public:
    DataModel(QObject *parent = nullptr);
    ~DataModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role
            ) const override;
    QVariant data(
            const QModelIndex &index,
            int role = Qt::DisplayRole
            ) const override;
    void print() const;
};


#endif // DATA_MODEL_HPP
