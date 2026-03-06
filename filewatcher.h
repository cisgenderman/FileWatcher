#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QTextStream>
#include <QTimer>
#include <QObject>
#include <QFileInfo>
#include <QVector>


class FileWatcher: public QObject
{
    Q_OBJECT
public:
    explicit FileWatcher(QObject *parent = nullptr);

    // Добавление файла для отслеживания
    void addFile(const QString &filePath);

    // Запуск отслеживания
    void startWatching();

    int filesCount() const;

private slots:
    // Слот для проверки состояния файлов
    void checkFiles();

private:
    // Структура для хранения информации о файле
    struct FileStatus
    {
        QString filePath;
        bool exists;
        qint64 size;

        FileStatus() : exists(false), size(0) {}
    };

    QVector<FileStatus> m_files;
    QVector<FileStatus> m_previousState;
    QTimer *m_timer;
    QTextStream m_cout;

    // Сравнение состояний и вывод изменений
    void compareAndNotify(int index);
};

#endif // FILEWATCHER_H
