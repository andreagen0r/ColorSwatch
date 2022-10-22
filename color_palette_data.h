#pragma once

#include <QColor>
#include <QList>
#include <QObject>
#include <QString>

class IColorPaletteRepository;

class ColorPaletteData : public QObject {
    Q_OBJECT

    Q_PROPERTY( QList<QColor> colors READ colors WRITE setColors NOTIFY colorsChanged )

public:
    explicit ColorPaletteData( QObject* parent = nullptr );

    QList<QColor>& colors();
    void setColors( const QList<QColor>& newColors );

    void add( const QColor& color, const QString& swatch );
    void removeAt( int index, const QString& swatch );
    void clear();
    void load( const QString& swatch );

signals:
    void colorsChanged();
    void beginInsert();
    void endInsert();
    void beginRemove( int index );
    void endRemove();
    void beginReset();
    void endReset();

private:
    QList<QColor> m_colors;
    IColorPaletteRepository* m_repository;

    void save( const QString& swatch );
};
