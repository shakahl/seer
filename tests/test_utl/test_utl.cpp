#include "../../src/SeerUtl.h"
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QRegExp>
#include <iostream>

int main (int argc, char** argv) {

    Q_UNUSED(argc);
    Q_UNUSED(argv);

    //
    //
    //

  //QString test = "\"r0\",\"\",\"\",\"r4\"";
    QString test = "\"\",\"r0\",\"\",\"r4\"";
    QString newtest = Seer::filterEscapes(test);

    std::cout << test.toStdString() << std::endl;
    std::cout << newtest.toStdString() << std::endl;

    QStringList list = Seer::parse(test, "", '"', '"', false);

    for ( const auto& name : list  ) {
        std::cout << name.toStdString() << std::endl;
    }

    //
    //
    //

    QString text = "1^done,value=\"0\"";

    if (text.contains(QRegExp("^([0-9]+)\\^"))) {
        qDebug() << text << "matches";
    }else{
        qDebug() << text << "doesn't match";
    }

    //
    //
    //

    QString text2 = "1^done,value=\"\\\"Hello, World!\\\"\"";

    qDebug() << text2;

    QStringList list2 = Seer::parse(text2, "value=", '"', '"', false);

    for ( const auto& name : list2  ) {
        std::cout << name.toStdString() << std::endl;
    }

    //
    //
    //

    QString text3 = "name = \"Pasveer, Ernie\", age = 60, salary = 0.25, location = {city = \"Houston\", state = \"Texas\", zip = 77063}";

    qDebug() << text3;

    QStringList list3 = Seer::parseCommaList(text3, '{', '}');

    for ( const auto& name : list3  ) {

        QStringPair pair = Seer::parseNameValue(name, '=');

        std::cout << name.toStdString() << std::endl;
        std::cout << pair.first.toStdString() << std::endl;
        std::cout << pair.second.toStdString() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

