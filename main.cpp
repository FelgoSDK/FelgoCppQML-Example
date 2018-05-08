#include <QApplication>
#include <VPApplication>

#include <QQmlApplicationEngine>

// include qml context, required to add a context property
#include <QQmlContext>

// include custom classes
#include "myglobalobject.h"
#include "myqmltype.h"

// uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
//#include <VPLiveClient>

int main(int argc, char *argv[])
{

  QApplication app(argc, argv);

  VPApplication vplay;

  // QQmlApplicationEngine is the preferred way to start qml projects since Qt 5.2
  // if you have older projects using Qt App wizards from previous QtCreator versions than 3.1, please change them to QQmlApplicationEngine
  QQmlApplicationEngine engine;
  vplay.initialize(&engine);

  // use this during development
  // for PUBLISHING, use the entry point below
  vplay.setMainQmlFileName(QStringLiteral("qml/Main.qml"));

  // use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
  // this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
  // to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
  // also see the .pro file for more details
  //  vplay.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));

  // add global c++ object to the QML context as a property
  MyGlobalObject* myGlobal = new MyGlobalObject();
  myGlobal->doSomething("TEXT FROM C++");
  engine.rootContext()->setContextProperty("myGlobalObject", myGlobal); // the object will be available in QML with name "myGlobalObject"

  // register a QML type made with C++
  qmlRegisterType<MyQMLType>("com.yourcompany.xyz", 1, 0, "MyQMLType"); // MyQMLType will be usable with: import com.yourcompany.xyz 1.0


  engine.load(QUrl(vplay.mainQmlFileName()));

  // to start your project as Live Client, comment (remove) the lines "vplay.setMainQmlFileName ..." & "engine.load ...",
  // and uncomment the line below
//  VPlayLiveClient client (&engine);

  return app.exec();
}
