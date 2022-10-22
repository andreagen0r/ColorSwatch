#include "swatches_qsettings_repository.h"

#include <QSettings>

SwatchesQSettingsRepository::~SwatchesQSettingsRepository() = default;

void SwatchesQSettingsRepository::save( const QList<SwatchItem>& itens ) {

    QSettings settings;
    settings.beginGroup( GROUP );

    for ( const auto& item : itens ) {
        settings.setValue( item.id, item.title );
    }

    settings.endGroup();
}

void SwatchesQSettingsRepository::saveCurrent( const QString& id ) {

    QSettings settings;
    settings.beginGroup( GROUP );
    settings.setValue( CURRENT_SWATCH, id );
    settings.endGroup();
}

void SwatchesQSettingsRepository::removeBy( const QString& id ) {

    QSettings settings;
    settings.beginGroup( GROUP );
    settings.remove( id );
    settings.endGroup();
}

const QString SwatchesQSettingsRepository::readCurrent() const {

    QSettings settings;
    settings.beginGroup( GROUP );
    const QString id = settings.value( "CURRENT_SWATCH" ).toString();
    settings.endGroup();
    return id;
}

QList<SwatchItem> SwatchesQSettingsRepository::readAll() const {

    QList<SwatchItem> out;
    QSettings settings;
    settings.beginGroup( GROUP );
    const auto keys = settings.allKeys();
    for ( const auto& key : keys ) {
        if ( key != CURRENT_SWATCH ) {
            out.append( SwatchItem { key, settings.value( key ).toString() } );
        }
    }
    settings.endGroup();

    return out;
}

SwatchItem SwatchesQSettingsRepository::findById( const QString& id ) const {

    SwatchItem out;
    QSettings settings;
    settings.beginGroup( GROUP );

    if ( settings.contains( id ) ) {
        out.id = id;
        out.title = settings.value( id ).toString();
    }
    settings.endGroup();

    return out;
}
