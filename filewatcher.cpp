#include "filewatcher.h"
#include <QDebug>

FileWatcher::FileWatcher(QObject *parent)
    : QObject(parent)
    , m_cout(stdout)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &FileWatcher::checkFiles);
}

void FileWatcher::addFile(const QString &filePath)
{
    FileStatus status;
    status.filePath = filePath;

    QFileInfo fileInfo(filePath);
    status.exists = fileInfo.exists();

    if (status.exists)
    {
        status.size = fileInfo.size();  // Файл есть - берем размер
    }
    else
    {
        status.size = 0;                 // Файла нет - размер 0
    }

    m_files.append(status);
    m_previousState.append(status);

    m_cout << "Добавлен файл для отслеживания: " << filePath << Qt::endl;
}

void FileWatcher::startWatching()
{
    if (m_files.isEmpty())
    {
        m_cout << "Нет файлов для отслеживания!" << Qt::endl;
        return;
    }
    checkFiles();
    m_timer->start(100);
}

void FileWatcher::checkFiles()
{
}

void FileWatcher::compareAndNotify(int index)
{
}


int FileWatcher::filesCount() const
{
    return m_files.size();
}


