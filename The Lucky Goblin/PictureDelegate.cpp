#pragma once

#include "PictureDelegate.h"

PictureDelegate::PictureDelegate(QWidget* parent)
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QString vision = index.model()->data(index, Qt::EditRole).toString();
    if (index.column() != 4)
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    ifstream readFile(vision.toStdString());
    if (!readFile)
        vision = "not found.jpg";
    readFile.close();

    QPixmap pixMap(vision);
    painter->drawPixmap(option.rect, pixMap);
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 4)
        return QSize(160, 130);

    return QStyledItemDelegate::sizeHint(option, index);
}
