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
        m_cout << "file exist" << Qt::endl;
        m_cout << "Size: " << fileInfo.size() << " byte" << Qt::endl;
        status.size = fileInfo.size();  // Файл есть - берем размер
    }
    else
    {
        m_cout << "file not exist" << Qt::endl;
        status.size = 0;                 // Файла нет - размер 0
    }

    m_files.append(status);
    m_previousState.append(status);

    m_cout << "add file to watch: " << filePath << Qt::endl;
}

void FileWatcher::startWatching()
{
    checkFiles();
    m_timer->start(100);
}

void FileWatcher::checkFiles()
{
    for (int i = 0; i < m_files.size(); ++i)
    {
        QFileInfo fileInfo(m_files[i].filePath);
        m_files[i].exists = fileInfo.exists();
        if (m_files[i].exists)
        {
            m_files[i].size = fileInfo.size();
        }
        else
        {
            m_files[i].size = 0;
        }

        if (m_files[i].exists != m_previousState[i].exists ||
            (m_files[i].exists && m_files[i].size != m_previousState[i].size))
        {
            compareAndNotify(i);
        }

        // Обновляем предыдущее состояние
        m_previousState[i] = m_files[i];
    }
}

void FileWatcher::compareAndNotify(int index)
{
    const FileStatus &current = m_files[index];
    const FileStatus &previous = m_previousState[index];

    // Проверяем существование файла
    if (!current.exists)
    {
        m_cout << "\nSTATUS: File " << index << " not exist" << Qt::endl;
        return;
    }
    // Файл существует
    if (!previous.exists)
    {
        // Файл только что появился
        m_cout << "\nSTATUS: File " << index << " created" << Qt::endl;
        m_cout << "Size: " << current.size << " byte" << Qt::endl;
    }
    // Файл был изменен
    else if (current.size != previous.size)
    {
        m_cout << "\nSTATUS: File " << index << " was changed" << Qt::endl;
        m_cout << "previous size: " << previous.size << " byte" << Qt::endl;
        m_cout << "current size: " << current.size << " byte" << Qt::endl;
    }
    // Файл существует и не изменялся (просто вывод информации)
    else
    {
        m_cout << "\nSTATUS: File " << index << " exist" << Qt::endl;
        m_cout << "Size: " << current.size << " byte" << Qt::endl;
    }
}


int FileWatcher::filesCount() const
{
    return m_files.size();
}




