#include "color_palette_model.h"
#include "color_palette_data.h"

ColorPaletteModel::ColorPaletteModel( QObject* parent )
    : QAbstractListModel { parent }
    , m_colorData( new ColorPaletteData( this ) ) {

    connect( m_colorData, &ColorPaletteData::beginInsert, this, [this] {
        const int index { static_cast<int>( m_colorData->colors().size() ) };
        beginInsertRows( QModelIndex(), index, index );
    } );

    connect( m_colorData, &ColorPaletteData::endInsert, this, [this] { endInsertRows(); } );

    connect( m_colorData, &ColorPaletteData::beginRemove, this, [this]( const int index ) { beginRemoveRows( QModelIndex(), index, index ); } );

    connect( m_colorData, &ColorPaletteData::endRemove, this, [this] { endRemoveRows(); } );

    connect( m_colorData, &ColorPaletteData::beginReset, this, [this] { beginResetModel(); } );

    connect( m_colorData, &ColorPaletteData::endReset, this, [this] { endResetModel(); } );
}

QColor ColorPaletteModel::colorAt( int index ) const {
    return m_colorData->colors().at( index );
}

void ColorPaletteModel::removeAt( int index, const QString& palette ) {

    if ( index < 0 || index >= m_colorData->colors().size() ) {
        return;
    }

    m_colorData->removeAt( index, palette );
}

void ColorPaletteModel::addColor( const QColor& color, const QString& palette ) {
    m_colorData->add( color, palette );
}

void ColorPaletteModel::clear() {
    m_colorData->clear();
}

void ColorPaletteModel::load( const QString& swatchId ) {
    m_colorData->load( swatchId );
}

int ColorPaletteModel::rowCount( const QModelIndex& parent ) const {

    if ( parent.isValid() || m_colorData == nullptr ) {
        return 0;
    }

    return static_cast<int>( m_colorData->colors().size() );
}

QVariant ColorPaletteModel::data( const QModelIndex& index, int role ) const {

    if ( !index.isValid() ) {
        return {};
    }

    const auto color = m_colorData->colors().at( index.row() );

    switch ( role ) {
        case ColorSwatch:
            return color;
    }

    return {};
}

QHash<int, QByteArray> ColorPaletteModel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[ColorSwatch] = QByteArrayLiteral( "ColorSwatch" );
    return roles;
}
