#pragma once

#include "EvidenceTreeModel.h"

#include <QtCore>

#include <tsk/libtsk.h>

class EvidenceTreeItem
{
};

class ImageItem : EvidenceTreeItem
{
    TSK_IMG_INFO *img_info;
    QList<EvidenceTreeItem> *partitionItems = new QList<EvidenceTreeItem>();

  public:
    explicit ImageItem(const char *path)
    {
        const char *images[] = {path};
        img_info = tsk_img_open(1, images, TSK_IMG_TYPE_DETECT, 0);
        const TSK_VS_INFO *vs_info = tsk_vs_open(img_info, 0, TSK_VS_TYPE_DETECT);
        for (int i = 0; i < vs_info->part_count; i++)
        {
            const TSK_VS_PART_INFO *part = tsk_vs_part_get(vs_info, i);

            if (part == nullptr)
                break;

            part;
        }
    }

    ~ImageItem()
    {
        tsk_img_close(img_info);
    }
};

class EvidenceTreeModel : QAbstractItemModel
{
    Q_OBJECT
  public:
    EvidenceTreeModel();
    ~EvidenceTreeModel() override;

  private:
    EvidenceTreeItem *rootItem;
};
