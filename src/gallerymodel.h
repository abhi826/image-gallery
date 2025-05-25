#pragma once

#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include <QUrl>

struct ImageItem { QString source; };

class GalleryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles { SourceRole = Qt::UserRole + 1 };

    explicit GalleryModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setCurrentIndex(int idx);
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
    int currentIndex() const { return m_currentIndex; }

    Q_INVOKABLE QUrl sourceAt(int row) const;

signals:
    void currentIndexChanged(int newIndex);

private:
    QVector<ImageItem> m_items;
    int m_currentIndex = -1;
};
