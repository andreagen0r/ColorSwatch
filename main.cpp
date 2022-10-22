#include <QApplication>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] ) {

    QApplication app( argc, argv );

    QCoreApplication::setOrganizationName( u"ACME"_qs );
    QCoreApplication::setOrganizationDomain( u"com.acme"_qs );
    QCoreApplication::setApplicationName( u"ColorSwatch"_qs );
    QCoreApplication::setApplicationVersion( "1.0.0" );

    QQmlApplicationEngine engine;
    const QUrl url( u"qrc:/ColorSwatch/main.qml"_qs );
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url]( QObject* obj, const QUrl& objUrl ) {
            if ( !obj && url == objUrl )
                QCoreApplication::exit( -1 );
        },
        Qt::QueuedConnection );
    engine.load( url );

    return app.exec();
}
