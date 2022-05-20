#include "albumControl.h"
#include "dbmanager/dbmanager.h"
#include "imageengine/movieservice.h"
#include <QUrl>

DBImgInfo getDBInfo(const QString &srcpath, bool isVideo)
{
    using namespace LibUnionImage_NameSpace;
    QFileInfo srcfi(srcpath);
    DBImgInfo dbi;
    dbi.filePath = srcpath;
    dbi.importTime = QDateTime::currentDateTime();
    if (isVideo) {
        dbi.itemType = ItemTypeVideo;
        //获取视频信息
        MovieInfo movieInfo = MovieService::instance()->getMovieInfo(QUrl::fromLocalFile(srcpath));

        dbi.changeTime = srcfi.lastModified();

        if (movieInfo.creation.isValid()) {
            dbi.time = movieInfo.creation;
        } else if (srcfi.birthTime().isValid()) {
            dbi.time = srcfi.birthTime();
        } else if (srcfi.metadataChangeTime().isValid()) {
            dbi.time = srcfi.metadataChangeTime();
        } else {
            dbi.time = dbi.changeTime;
        }
    } else {
        auto mds = getAllMetaData(srcpath);
        QString value = mds.value("DateTimeOriginal");
        dbi.itemType = ItemTypePic;
        dbi.changeTime = QDateTime::fromString(mds.value("DateTimeDigitized"), "yyyy/MM/dd hh:mm");
        if (!value.isEmpty()) {
            dbi.time = QDateTime::fromString(value, "yyyy/MM/dd hh:mm");
        } else if (srcfi.birthTime().isValid()) {
            dbi.time = srcfi.birthTime();
        } else if (srcfi.metadataChangeTime().isValid()) {
            dbi.time = srcfi.metadataChangeTime();
        } else {
            dbi.time = dbi.changeTime;
        }
    }
    return dbi;
}

AlbumControl::AlbumControl(QObject *parent) : QObject(parent)
{

}

AlbumControl::~AlbumControl()
{

}

void AlbumControl::getAllInfos()
{
    m_infoList = DBManager::instance()->getAllInfos();
}

QStringList AlbumControl::getAllPaths()
{
    QStringList pathList;
    QStringList list = DBManager::instance()->getAllPaths();
    for(QString path : list){
        pathList << "file://"+ path;
    }
    return pathList;
}

void AlbumControl::importAllImagesAndVideos(const QList< QUrl > &paths)
{
    QStringList localpaths;
    DBImgInfoList dbInfos;
    for(QUrl path : paths){
        localpaths << path.toLocalFile();
    }
    QStringList curAlbumImgPathList = getAllPaths();
    for(QString imagePath : localpaths){
        bool bIsVideo = LibUnionImage_NameSpace::isVideo(imagePath);
        if (!bIsVideo && !LibUnionImage_NameSpace::imageSupportRead(imagePath)) {
            continue;
        }
        QFileInfo srcfi(imagePath);
        if (!srcfi.exists()) {  //当前文件不存在
            continue;
        }
        if (curAlbumImgPathList.contains(imagePath)) {
        }
        DBImgInfo info =  getDBInfo(imagePath, bIsVideo);
        dbInfos << info;
    }
    std::sort(dbInfos.begin(), dbInfos.end(), [](const DBImgInfo & lhs, const DBImgInfo & rhs) {
        return lhs.changeTime > rhs.changeTime;
    });
    //已全部存在，无需导入
    if (dbInfos.size() > 0) {
        //导入图片数据库ImageTable3
        DBManager::instance()->insertImgInfos(dbInfos);
    }

}