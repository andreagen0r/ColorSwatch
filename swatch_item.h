#pragma once

#include <QString>

struct SwatchItem {

    SwatchItem() = default;
    SwatchItem( const QString& id, const QString& title )
        : id { id }
        , title { title } { }

    QString id;
    QString title;
};
