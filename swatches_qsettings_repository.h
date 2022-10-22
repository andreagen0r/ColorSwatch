#pragma once

#include "iswatches_repository.h"

class SwatchesQSettingsRepository : public ISwatchesRepository {

public:
    ~SwatchesQSettingsRepository() override;

    void save( const QList<SwatchItem>& itens ) override;
    void saveCurrent( const QString& id ) override;
    void removeBy( const QString& id ) override;
    const QString readCurrent() const override;
    QList<SwatchItem> readAll() const override;
    SwatchItem findById( const QString& id ) const override;
};
