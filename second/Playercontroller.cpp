#include "Playercontroller.h"

PlayerController::PlayerController(QObject *parent)
    : QAbstractListModel{parent}
{
    addAudio("Hello ahoaoa","kkddkkdkdd",QUrl("assets/audio/video1.mp3"),QUrl("assets/icons/First.png"));
    addAudio("May thich gif","hehe lele",QUrl("assets/audio/video2.mp3"),QUrl("assets/icons/second.png"));
    addAudio("Co gi vui ne","chaksksk",QUrl("assets/audio/video3.mp3"),QUrl("assets/icons/third.png"));


}



bool PlayerController::playing() const
{
    return m_playing;
}

void PlayerController::switchToNextSong()
{

    int index=m_audioList.indexOf(m_currentSong);
    index=(index+1)%(int)m_audioList.size();
    setCurrentSong(m_audioList[index]);
}

int PlayerController::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.length();
}

QVariant PlayerController::data(const QModelIndex &index, int role) const
{
    if (index.isValid()&&index.row()>=0&&index.row()<m_audioList.length()) {
        AudioInfo * audioInfo=m_audioList[index.row()];
        switch ((Role)role) {
        case AudioTitleRole:
            return audioInfo->title();
            break;
        case AudioAuthorNameRole:
            return audioInfo->authorName();break;
        case AudioSourceRole:
            return audioInfo->audioSource(); break;
        case AudioImageSourceRole:
            return audioInfo->imageSource(); break;
        case AudioVideoSourceRole:
            return audioInfo->videoSource(); break;

        }
    }
    return {};
}

QHash<int, QByteArray> PlayerController::roleNames() const
{
    QHash<int,QByteArray> result;
    result[AudioAuthorNameRole]="audioAuthorName";
    result[AudioTitleRole]="audioTitle";
    result[AudioSourceRole]="audioSource";
    result[AudioImageSourceRole]="audioImageSource";
    result[AudioVideoSourceRole]="audioVideoSource";
    return result;

}

AudioInfo *PlayerController::currentSong() const
{
    return m_currentSong;
}

void PlayerController::setCurrentSong(AudioInfo *newCurrentSong)
{
    if (m_currentSong==newCurrentSong) return;
    m_currentSong=newCurrentSong;
    emit currentSongChanged();
    if (m_currentSong) {

    } else {
        m_playing=false;
        emit playingChanged();
    }
}

void PlayerController::switchToPreviousSong()
{
    int index=m_audioList.indexOf(m_currentSong);
    index=(index-1+(int)m_audioList.size())%(int)m_audioList.size();
    setCurrentSong(m_audioList[index]);
}

void PlayerController::playPause()
{
    m_playing=!m_playing;
    emit playingChanged();
}

void PlayerController::changeAudioSouce(QUrl &source)
{

}

void PlayerController::addAudio(const QString &title, const QString &authorName, const QUrl &audioSource, const QUrl &imageSource, const QUrl &videoSource)
{
    beginInsertColumns(QModelIndex(),m_audioList.length(),m_audioList.length());
    AudioInfo *audioInfo=new AudioInfo(this);
    audioInfo->setTitle(title);
    audioInfo->setAuthorName(authorName);
    audioInfo->setAudioSource(audioSource);
    audioInfo->setImageSource(imageSource);
    audioInfo->setVideoSource(videoSource);
    if (m_audioList.isEmpty()) setCurrentSong(audioInfo);
    m_audioList<<audioInfo;
    endInsertRows();
}

void PlayerController::removeAudio(int index)
{
    if (index>=0&&index<m_audioList.length()) {
        beginRemoveRows(QModelIndex(),index,index);
        AudioInfo * toRemove=m_audioList[index];
        if (toRemove==m_currentSong) {
            if (m_audioList.length()>1) {
                if (index!=0) {
                    setCurrentSong(m_audioList[index-1]);
                } else {
                    setCurrentSong(m_audioList[index+1]);
                }
            } else {
                setCurrentSong(nullptr);
            }
        }
        m_audioList.removeAt(index);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

void PlayerController::switchToAudioByIndex(int index)
{
    if (index>=0&&index<m_audioList.length()) {
        setCurrentSong(m_audioList[index]);
    }
}
