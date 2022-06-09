#ifndef AlbumControl_H
#define AlbumControl_H

#include <QObject>
#include <QUrl>
#include "unionimage/unionimage.h"
#include "dbmanager/dbmanager.h"


class FileInotifyGroup;

class AlbumControl : public QObject
{
    Q_OBJECT
public:

    enum TimeLineEnum {
        All  = 0,
        Year = 1,
        Month  = 2,
        Day = 3,
        Import = 4
    };

    explicit AlbumControl(QObject *parent = nullptr);
    ~  AlbumControl();

    //获得全部导入的DBImgInfoList
    Q_INVOKABLE void getAllInfos();

    //获得全部导入的路径
    Q_INVOKABLE QStringList getAllPaths();

    //导入图片，导入图片接口
    Q_INVOKABLE void importAllImagesAndVideos(const QList< QUrl > &paths);

    //获得全部创建时间线
    Q_INVOKABLE QStringList getAllTimelinesTitle(const int &filterType = 0);

    //获得年创建时间线
    Q_INVOKABLE QStringList getYearTimelinesTitle(const int &filterType = 0);

    //获得月创建时间线
    Q_INVOKABLE QStringList getMonthTimelinesTitle(const int &filterType = 0);

    //获得日创建时间线
    Q_INVOKABLE QStringList getDayTimelinesTitle(const int &filterType = 0);

    //获得某一创建时间线的全部路径
    Q_INVOKABLE QStringList getTimelinesTitlePaths(const QString &titleName, const int &filterType);

    //获得全部已经导入
    Q_INVOKABLE QStringList getAllImportTimelinesTitle(const int &filterType = 0);

    //获得某一导入时间的全部路径
    Q_INVOKABLE QStringList getImportTimelinesTitlePaths(const QString &titleName, const int &filterType = 0);

    //QVariantMap接口
    //获得默认时间线的全部info  , 0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getTimelinesTitleInfos(const int &filterType = 0);

    //获得年创建时间线 0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getYearTimelinesInfos(const int &filterType = 0);

    //获得月创建时间线  0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getMonthTimelinesInfos(const int &filterType = 0);

    //获得月创建时间线  0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getDayTimelinesInfos(const int &filterType = 0);

    //获得某一导入时间线的全部info  , 0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getImportTimelinesTitleInfos(const int &filterType = 0);

    //获得图片和视频总数
    Q_INVOKABLE int getCount();

    //将文件放进最近删除(添加)
    Q_INVOKABLE void insertTrash(const QList< QUrl > &paths);

    //删除最近删除里面的文件
    Q_INVOKABLE void removeTrashImgInfos(const QList< QUrl > &paths);

    //恢复文件 //返回无法恢复的文件
    Q_INVOKABLE QStringList recoveryImgFromTrash(const QStringList &paths);

    //将文件放进收藏中(添加)
    Q_INVOKABLE void insertCollection(const QList< QUrl > &paths);

    //新建相册
    Q_INVOKABLE void createAlbum(const QString &newName);

    //获得所有的自定义相册id
    Q_INVOKABLE QList < int > getAllCustomAlbumId();

    //获得所有的自定义相册名称
    Q_INVOKABLE QList < QString > getAllCustomAlbumName();

    //获得自定义的相册的全部info  albumId 0:我的收藏  1:截图录屏  2:相机 3:画板 4-~:其他自定义,filterType 0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getAlbumInfos(const int &albumId, const int &filterType = 0);

    //获得最近删除的相册的全部info  , 0:全部 1:图片 2:视频
    Q_INVOKABLE QVariantMap getTrashAlbumInfos(const int &filterType = 0);

    //添加到自定义相册
    Q_INVOKABLE bool addCustomAlbumInfos(const int &albumId, const QList <QUrl> &urls, const int &imoprtType = 0);

    //根据自定义相册id获取相册名称
    Q_INVOKABLE QString getCustomAlbumByUid(const int &index);

    //判断当前图片是否已收藏
    Q_INVOKABLE bool photoHaveFavorited(const QString &path);

    //判断所传图片列表是否可收藏
    Q_INVOKABLE bool canFavorite(const QStringList &pathList);

    //一张图片的数据，返回Map
    Q_INVOKABLE QVariantMap getPathsInfoMap(const QString &path);

    //一张图片的数据，返回List
    Q_INVOKABLE QStringList getPathsInfoList(const QString &path);

    //一张图片的数据，返回Data
    Q_INVOKABLE QString getPathsInfoData(const QString &path, const QString &key);

    //获得自定义相册图片count 0:我的收藏  1:截图录屏  2:相机 3:画板 4-~:其他自定义,filterType 0:全部 1:图片 2:视频
    Q_INVOKABLE int getCustomAlbumInfoConut(const int &albumId, const int &filterType = 0);

    //全部导入的info的count filterType 0:全部 1:图片 2:视频
    Q_INVOKABLE int getAllInfoConut(const int &filterType = 0);

    //全部最近删除info的count filterType 0:全部 1:图片 2:视频
    Q_INVOKABLE int getTrashInfoConut(const int &filterType = 0);

    //删除相册 0:我的收藏  1:截图录屏  2:相机 3:画板 4-~:其他自定义
    Q_INVOKABLE void removeAlbum(int UID);

    //删除某相册中的图片 0:我的收藏  1:截图录屏  2:相机 3:画板 4-~:其他自定义   paths:需要删除的图片地址
    Q_INVOKABLE void removeFromAlbum(int UID, const QStringList &paths);

    //添加某相册中的图片 0:我的收藏  1:截图录屏  2:相机 3:画板 4-~:其他自定义   paths:需要删除的图片地址
    Q_INVOKABLE bool insertIntoAlbum(int UID, const QStringList &paths);

    //使用关键字在指定位置执行搜索 UID:相册的标识符，-1表示进行全数据库搜索，-2表示搜索最近删除；keywords:搜索依据
    //useAI为保留参数，false:不使用AI，只根据文件路径搜索；true:使用AI进行分析，根据关键字含义和图片内容进行搜索
    Q_INVOKABLE QVariant searchPicFromAlbum(int UID, const QString &keywords, bool useAI);

    //输入一张图片，获得可以导出的格式
    Q_INVOKABLE QStringList imageCanExportFormat(const QString &path);

    //输入一张图片，获得可以导出的格式
    Q_INVOKABLE bool saveAsImage( const QString &path ,const QString &saveName , int index ,const QString &fileFormat  , int pictureQuality = 100 , const QString &saveFolder = nullptr);

    //获得选择路径
    Q_INVOKABLE QString getFolder();

    //用影院打开视频
    Q_INVOKABLE void openDeepinMovie(const QString &path);

public :
    QString getDeleteFullPath(const QString &hash, const QString &fileName);

    //获得最近删除的文件
    DBImgInfoList getTrashInfos(const int &filterType = 0);

    //获得收藏文件
    DBImgInfoList getCollectionInfos();

    //获得画板文件
    DBImgInfoList getDrawInfos();

    //获得截图录屏文件
    DBImgInfoList getScreenCaptureInfos();

    //获得相机文件
    DBImgInfoList getCameraInfos();

    //新相册名称
    const QString getNewAlbumName(const QString &baseName);

    //获得日月年所有创建时间线  0所有 1年 2月 3日
    QStringList getTimelinesTitle(TimeLineEnum timeEnum, const int &filterType = 0);

    //初始化
    void initMonitor();

    //启动路径监控
    void startMonitor();

    //是否已经处于监控
    bool checkIfNotified(const QString &dirPath);


public slots:
    //监控到改变
    void slotMonitorChanged(QStringList fileAdd, QStringList fileDelete, QString album, int UID);

    //自动导入路径被删除
    void slotMonitorDestroyed(int UID);

signals:
   void sigRefreshCustomAlbum(int UID);
   void sigRefreshImportAlbum();

   //自定义相册删除
   void sigDeleteCustomAlbum(int UID);


private :
    DBImgInfoList m_infoList;  //全部已导入

    //时间线数据和已导入（合集）数据
    QList < QDateTime > m_timelines; //所有创建时间线
    QList < QDateTime > m_importTimelines; //所有已导入时间线
    QMap < QString, DBImgInfoList > m_importTimeLinePathsMap;  //每个已导入时间线的路径
    QMap < QString, DBImgInfoList > m_timeLinePathsMap;  //每个创建时间线的路径
    QMap < QString, DBImgInfoList > m_yearDateMap; //年数据集
    QMap < QString, DBImgInfoList > m_monthDateMap; //月数据集
    QMap < QString, DBImgInfoList > m_dayDateMap; //日数据集
    QMap < int, QString > m_customAlbum; //自定义相册

    FileInotifyGroup * m_fileInotifygroup {nullptr};//固定文件夹监控


};

#endif // AlbumControl_H
