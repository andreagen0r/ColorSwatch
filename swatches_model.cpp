#include "swatches_model.h"

#include <QUuid>

#include "swatches_qsettings_repository.h"

SwatchesModel::SwatchesModel( QObject* parent )
    : QAbstractListModel { parent }
    , m_repository { new SwatchesQSettingsRepository() } {

    createDefault();
}

void SwatchesModel::add( const QString& title ) {

    SwatchItem swatch { QUuid::createUuid().toString( QUuid::WithoutBraces ), title };

    beginInsertRows( QModelIndex(), m_palettes.size(), m_palettes.size() );
    m_palettes.append( swatch );
    endInsertRows();

    m_repository->save( m_palettes );

    Q_EMIT swatchAdded();
}

void SwatchesModel::setCurrentSwatch( const QString& value ) {
    m_repository->saveCurrent( value );
}

void SwatchesModel::removeByID( const QString& id ) {

    beginResetModel();
    m_palettes.removeIf( [&]( auto item ) { return item.id == id; } );
    m_palettes.shrink_to_fit();
    endResetModel();

    m_repository->removeBy( id );
}

QString SwatchesModel::currentSwatch() const {
    return m_repository->readCurrent();
}

int SwatchesModel::rowCount( const QModelIndex& parent ) const {

    if ( parent.isValid() ) {
        return 0;
    }

    return m_palettes.size();
}

QVariant SwatchesModel::data( const QModelIndex& index, int role ) const {

    if ( !index.isValid() ) {
        return {};
    }

    const auto currentPalette = m_palettes.at( index.row() );

    switch ( static_cast<SwatchRoles>( role ) ) {
        case SwatchRoles::Text:
            return currentPalette.title;
        case SwatchRoles::Value:
            return currentPalette.id;
    }

    return {};
}

QHash<int, QByteArray> SwatchesModel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[static_cast<int>( SwatchRoles::Text )] = QByteArrayLiteral( "Title" );
    roles[static_cast<int>( SwatchRoles::Value )] = QByteArrayLiteral( "Value" );
    return roles;
}

void SwatchesModel::createDefault() {

    const SwatchItem defaultItem { u"9fc955b4-95d7-4db8-a481-eab6328754d6"_qs, tr( "Default" ) };
    const auto item = m_repository->findById( defaultItem.id );
    if ( item.id.isNull() or item.id.isEmpty() ) {
        m_palettes.append( defaultItem );
        Q_EMIT defaultSwatchAdded();
        return;
    }

    m_palettes = m_repository->readAll();
}
