#include <QCoreApplication>
#include <QTextStream>
#include "filewatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout);
    QTextStream cin(stdin);

    cout << "Enter file paths to watch (empty line to start):" << Qt::endl;

    FileWatcher watcher;
    QString line;

    // Ввод файлов для отслеживания
    do
    {
        cout << "> ";
        cout.flush();
        line = cin.readLine();

        if (!line.isEmpty())
        {
            watcher.addFile(line);
        }
    }
    while (!line.isEmpty());

    if (watcher.filesCount() == 0)
    {
        cout << "\nNot add any file. exit" << Qt::endl;
        return 0;
    }

    // Запуск отслеживания
    watcher.startWatching();

    return a.exec();
}
