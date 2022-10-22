#pragma once

#include "icolor_palette_repository.h"

class ColorPaletteQSettingsRepository : public IColorPaletteRepository {

public:
    ColorPaletteQSettingsRepository();

    void save( const QList<QColor>& colors, const QString& swatchName ) override;
    QList<QColor> readAll( const QString& swatchName ) const override;
    bool isValid() const override;
    QString currentSwatchId() const override;
};
