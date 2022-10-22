#pragma once

#include <QAbstractListModel>
#include <QColor>
#include <QList>
#include <QObject>
#include <QQmlEngine>

class ColorPaletteData;

class ColorPaletteModel : public QAbstractListModel {

    Q_OBJECT
    QML_ELEMENT

public:
    explicit ColorPaletteModel( QObject* parent = nullptr );

    // clang-format off
  enum Roles {
    ColorSwatch = Qt::UserRole + 1
  };
    // clang-format on

    [[nodiscard]] Q_INVOKABLE QColor colorAt( int index ) const;
    Q_INVOKABLE void removeAt( int index, const QString& palette );
    Q_INVOKABLE void addColor( const QColor& color, const QString& palette );
    Q_INVOKABLE void clear();
    Q_INVOKABLE void load( const QString& swatchId );

    [[nodiscard]] int rowCount( const QModelIndex& parent ) const override;
    [[nodiscard]] QVariant data( const QModelIndex& index, int role ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

private:
    ColorPaletteData* m_colorData;
};
