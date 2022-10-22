#pragma once

#include <QList>
#include <QColor>

class IColorPaletteRepository {

public:
    virtual ~IColorPaletteRepository() = default;
    virtual void save( const QList<QColor>& colors, const QString& swatchName ) = 0;
    virtual QList<QColor> readAll( const QString& swatchName ) const = 0;
    virtual bool isValid() const = 0;
    virtual QString currentSwatchId() const = 0;

protected:
    inline static const QString GROUP { u"COLOR_PALETTE"_qs };
    static inline const QString SWATCHES_GROUP { u"SWATCHES"_qs };
    inline static const QString CURRENT_SWATCH { u"CURRENT_SWATCH"_qs };
    inline static const QString COLOR_KEY { u"COLOR"_qs };
};
