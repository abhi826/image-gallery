#include "gallerymodel.h"

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QImageReader>

GalleryModel::GalleryModel(QObject* parent)
    : QAbstractListModel(parent)
{
    // Determine which folder to scan
    const QString picturesDir =
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    qDebug() << "Scanning for images in" << picturesDir;

    QDir dir(picturesDir);
    // Filter by common image extensions
    QStringList filters = { "*.png", "*.jpg", "*.jpeg", "*.gif",
                            "*.bmp", "*.webp", "*.tif", "*.tiff" };

    for (const auto& file : dir.entryList(filters, QDir::Files)) {
        const auto& absPath = dir.filePath(file);

        // Use QImageReader to verify Qt can actually decode the file
        QImageReader reader(absPath);
        if (!reader.canRead()) {
            qWarning() << "Skipping unsupported or corrupt image:" << absPath;
            continue;                           // skip bad files
        }
        m_items.append({ absPath });
    }

    qDebug() << "Accepted" << m_items.size() << "images.";

    if (!m_items.isEmpty())
        setCurrentIndex(0);                     // select first image by default
}

/* ------------------------------------------------------------------ */
/*  QAbstractItemModel overrides                                       */
/* ------------------------------------------------------------------ */
int GalleryModel::rowCount(const QModelIndex&) const
{
    return m_items.size();
}

QVariant GalleryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return {};

    if (role == SourceRole)
        return m_items.at(index.row()).source;

    return {};
}

QHash<int, QByteArray> GalleryModel::roleNames() const
{
    return { { SourceRole, "source" } };
}

/* ------------------------------------------------------------------ */
/*  Invokable helpers                                                  */
/* ------------------------------------------------------------------ */
void GalleryModel::setCurrentIndex(int idx)
{
    if (idx < 0 || idx >= m_items.size() || idx == m_currentIndex)
        return;
    m_currentIndex = idx;
    emit currentIndexChanged(idx);
}

QUrl GalleryModel::sourceAt(int row) const
{
    if (row < 0 || row >= m_items.size())
        return QUrl();
    return QUrl::fromLocalFile(m_items.at(row).source);
}
