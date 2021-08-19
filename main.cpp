#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QBuffer>
#include <QByteArray>
#include <QTextStream>
#include <QString>
#include <QDataStream>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include "simplecrypt.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList fileNames;
    QString fileNames2;
    QString dirPath;
    cout << "Enter Dir Path :";
    std::string myStr ;
    std::getline(std::cin, myStr);
    qInfo() << "you entered :" << QString::fromStdString(myStr);
    /////QDir directory("G:/Projects/Qt C++/qtcrypt-files/nn/");
    dirPath = QString::fromStdString(myStr);
    QDir directory(dirPath);
    QStringList filter;
    filter << "*.enc";
    QDirIterator it(directory.path(), filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFile file2(it.next());
        if (!file2.open(QIODevice::ReadOnly)){
            qInfo() << "cant open file";
            return -1;
        };
        QDataStream in(&file2);
        QByteArray myCypherText = file2.readAll();
        file2.close();
        fileNames2 = file2.fileName() + ".jpg";
        QFile file3(fileNames2);
        file3.open(QIODevice::WriteOnly);
        SimpleCrypt crypto2(Q_UINT64_C(0x0c2ad4a4acb9f023)); //same random number: key should match encryption key
        QByteArray plaintext = crypto2.decryptToByteArray(myCypherText);
        QBuffer buffer2(&plaintext);
        buffer2.open(QIODevice::WriteOnly);
        QDataStream s2(&buffer2);
        file3.write(plaintext.data(), plaintext.size());
        //etc.
        buffer2.close();
        file3.close();

    }



    //// qInfo() << myCypherText;






}
