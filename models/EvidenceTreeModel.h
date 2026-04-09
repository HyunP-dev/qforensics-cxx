#pragma once

#include "EvidenceTreeModel.h"

#include <QtCore>

#include <tsk/libtsk.h>

class EvidenceTreeItem
{
  public:
    virtual ~EvidenceTreeItem() = default;
};

class PartitionItem : public EvidenceTreeItem
{
    TSK_FS_INFO *fs_info;

  public:
    explicit PartitionItem(TSK_IMG_INFO *img_info, TSK_DADDR_T offset);
};

class ImageItem : public EvidenceTreeItem
{
    TSK_IMG_INFO *img_info;
    QList<PartitionItem *> *partitionItems = new QList<PartitionItem *>();
    const char *path;

  public:
    explicit ImageItem(const char *path);

    ~ImageItem() override;

    [[nodiscard]] const char *getImagePath() const;
};

class DirectoryItem : public EvidenceTreeItem
{
};

class EvidenceTreeRootItem : public EvidenceTreeItem
{
  public:
    QList<ImageItem *> *imageItems = new QList<ImageItem *>();
};

class EvidenceTreeModel : public QAbstractItemModel
{
    Q_OBJECT
  public:
    EvidenceTreeModel();
    ~EvidenceTreeModel() override;

    void attachImage(const char *path);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]] QModelIndex parent(const QModelIndex &child) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent) const override;

  private:
    EvidenceTreeRootItem *rootItem = new EvidenceTreeRootItem();
};
