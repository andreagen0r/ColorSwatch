#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>

#include "swatch_item.h"

class ISwatchesRepository;

class SwatchesModel : public QAbstractListModel {

    Q_OBJECT
    QML_ELEMENT

public:
    explicit SwatchesModel( QObject* parent = nullptr );

    // clang-format off
    enum class SwatchRoles {
        Text = Qt::UserRole + 1,
        Value ,
    };
    // clang-format on

    Q_INVOKABLE void add( const QString& title );
    Q_INVOKABLE void setCurrentSwatch( const QString& value );
    Q_INVOKABLE void removeByID( const QString& id );
    [[nodiscard]] Q_INVOKABLE QString currentSwatch() const;
    [[nodiscard]] int rowCount( const QModelIndex& parent ) const override;
    [[nodiscard]] QVariant data( const QModelIndex& index, int role ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

Q_SIGNALS:
    void defaultSwatchAdded();
    void swatchAdded();

private:
    QList<SwatchItem> m_palettes;
    ISwatchesRepository* m_repository;

    void createDefault();
};
