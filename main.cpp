#include <QCoreApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout);

    cout << "Введите пути к файлам для отслеживания" << Qt::endl;
    QString line;

    // Ввод файлов для отслеживания
    do
    {
        cout << "> ";
        cout.flush();
        line = cout.readLine();

        if (!line.isEmpty())
        {
            watcher.addFile(line);
        }
    }
    while (!line.isEmpty());

    if (watcher.filesCount() == 0)
    {
        cout << "\nНе добавлено ни одного файла. Программа завершена." << Qt::endl;
        return 0;
    }

    // Запуск отслеживания
    watcher.startWatching();

    return a.exec();
}
