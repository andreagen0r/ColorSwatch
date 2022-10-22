#include "color_palette_data.h"

#include "color_palette_qsettings_repository.h"
#include "iswatches_repository.h"

ColorPaletteData::ColorPaletteData( QObject* parent )
    : QObject { parent }
    , m_repository { new ColorPaletteQSettingsRepository() } {

    if ( m_repository->isValid() ) {
        load( m_repository->currentSwatchId() );
        save( m_repository->currentSwatchId() );
    } else {
        for ( const auto& color : QColor::colorNames() ) {
            m_colors.append( QColor( color ) );
        }
        save( ISwatchesRepository::DEFAULT_ID );
    }
}

QList<QColor>& ColorPaletteData::colors() {
    return m_colors;
}

void ColorPaletteData::setColors( const QList<QColor>& newColors ) {
    if ( m_colors == newColors ) {
        return;
    }

    m_colors = newColors;
    emit colorsChanged();
}

void ColorPaletteData::add( const QColor& color, const QString& swatch ) {
    Q_EMIT beginInsert();
    m_colors.append( color );
    Q_EMIT endInsert();
    save( swatch );
}

void ColorPaletteData::removeAt( int index, const QString& swatch ) {
    Q_EMIT beginRemove( index );
    m_colors.removeAt( index );
    Q_EMIT endRemove();
    save( swatch );
}

void ColorPaletteData::clear() {
    Q_EMIT beginReset();
    m_colors.clear();
    Q_EMIT endReset();
}

void ColorPaletteData::save( const QString& swatch ) {
    m_repository->save( m_colors, swatch );
}

void ColorPaletteData::load( const QString& swatch ) {
    Q_EMIT beginReset();
    m_colors = m_repository->readAll( swatch );
    Q_EMIT endReset();
}
