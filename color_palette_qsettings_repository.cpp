#include "color_palette_qsettings_repository.h"

#include <QSettings>

void ColorPaletteQSettingsRepository::save( const QList<QColor>& colors, const QString& swatchName ) {

    QSettings settings;
    settings.beginGroup( GROUP );
    settings.beginWriteArray( swatchName );

    for ( int i = 0; const auto& color : colors ) {
        settings.setArrayIndex( i );
        settings.setValue( COLOR_KEY, color );
        ++i;
    }

    settings.endArray();
    settings.endGroup();
}

QList<QColor> ColorPaletteQSettingsRepository::readAll( const QString& swatchName ) const {

    QSettings settings;
    settings.beginGroup( GROUP );
    const int size = settings.beginReadArray( swatchName );

    QList<QColor> out;

    for ( int i = 0; i < size; ++i ) {
        settings.setArrayIndex( i );
        out.append( settings.value( COLOR_KEY ).value<QColor>() );
    }

    settings.endArray();
    settings.endGroup();

    return out;
}

bool ColorPaletteQSettingsRepository::isValid() const {

    QSettings settings;
    settings.beginGroup( SWATCHES_GROUP );
    const bool out = settings.contains( CURRENT_SWATCH );
    settings.endGroup();

    return out;
}

QString ColorPaletteQSettingsRepository::currentSwatchId() const {

    QSettings settings;
    settings.beginGroup( SWATCHES_GROUP );
    const auto out = settings.value( CURRENT_SWATCH ).toString();
    settings.endGroup();

    return out;
}
