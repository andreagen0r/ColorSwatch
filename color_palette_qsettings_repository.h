#pragma once

#include "icolor_palette_repository.h"

class ColorPaletteQSettingsRepository : public IColorPaletteRepository {
public:
    ColorPaletteQSettingsRepository() = default;

    void save( const QList<QColor>& colors, const QString& swatchName ) override;
    [[nodiscard]] QList<QColor> readAll( const QString& swatchName ) const override;
    [[nodiscard]] bool isValid() const override;
    [[nodiscard]] QString currentSwatchId() const override;
    Q_DISABLE_COPY( ColorPaletteQSettingsRepository )
};
