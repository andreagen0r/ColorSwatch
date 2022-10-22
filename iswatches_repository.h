#pragma once

#include <QList>

#include "swatch_item.h"

class ISwatchesRepository {

public:
    virtual ~ISwatchesRepository() = default;
    virtual void save( const QList<SwatchItem>& itens ) = 0;
    virtual void saveCurrent( const QString& id ) = 0;
    virtual void removeBy( const QString& id ) = 0;
    virtual const QString readCurrent() const = 0;
    virtual QList<SwatchItem> readAll() const = 0;
    virtual SwatchItem findById( const QString& id ) const = 0;

    static inline const QString DEFAULT_ID { u"9fc955b4-95d7-4db8-a481-eab6328754d6"_qs };

protected:
    static inline const QString GROUP { u"SWATCHES"_qs };
    static inline const QString CURRENT_SWATCH { u"CURRENT_SWATCH"_qs };
};
