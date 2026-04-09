#include "EvidenceTreeModel.h"

PartitionItem::PartitionItem(TSK_IMG_INFO *img_info, const TSK_DADDR_T offset)
{
    fs_info = tsk_fs_open_img(img_info, offset * img_info->sector_size, TSK_FS_TYPE_DETECT);
}

ImageItem::ImageItem(const char *path) : path(path)
{
    const char *images[] = {path};
    img_info = tsk_img_open(1, images, TSK_IMG_TYPE_DETECT, 0);
    const TSK_VS_INFO *vs_info = tsk_vs_open(img_info, 0, TSK_VS_TYPE_DETECT);
    for (int i = 0; i < vs_info->part_count; i++)
    {
        const TSK_VS_PART_INFO *part = tsk_vs_part_get(vs_info, i);

        if (part == nullptr)
            break;

        partitionItems->append(new PartitionItem(img_info, part->start));
    }
}

ImageItem::~ImageItem()
{
    tsk_img_close(img_info);
}

const char *ImageItem::getImagePath() const
{
    return path;
}

EvidenceTreeModel::EvidenceTreeModel() = default;

EvidenceTreeModel::~EvidenceTreeModel() = default;

void EvidenceTreeModel::attachImage(const char *path)
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    rootItem->imageItems->append(new ImageItem(path));
    endInsertRows();
}

int EvidenceTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
    {
        return rootItem->imageItems->size();
    }

    return 0;
}

int EvidenceTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QModelIndex EvidenceTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return {};

    auto *item = static_cast<EvidenceTreeItem *>(child.internalPointer());

    if (auto image_item = dynamic_cast<ImageItem *>(item))
    {
        return QModelIndex();
    }

    if (auto partition_item = dynamic_cast<PartitionItem *>(item))
    {
    }

    return QModelIndex();
}

QVariant EvidenceTreeModel::data(const QModelIndex &index, int role) const
{
    auto *item = static_cast<EvidenceTreeItem *>(index.internalPointer());
    if (role == Qt::DisplayRole)
    {
        if (auto image_item = dynamic_cast<ImageItem *>(item))
        {
            return QString(image_item->getImagePath()).split("/").last();
        }
    }
    return QVariant();
}

QModelIndex EvidenceTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    if (!parent.isValid())
    {
        const auto child = rootItem->imageItems->at(row);
        return createIndex(row, column, child);
    }

    return {};
}
