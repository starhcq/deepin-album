#ifndef IMPORTTIMELINEVIEW_H
#define IMPORTTIMELINEVIEW_H

#include "application.h"
#include "controller/signalmanager.h"
#include "dbmanager/dbmanager.h"
#include "widgets/thumbnaillistview.h"
#include "widgets/timelinelist.h"
#include "widgets/timelineitem.h"
#include "importview/importview.h"
#include "widgets/statusbar.h"
#include "allpicview/allpicview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <DListWidget>
#include <DCommandLinkButton>
#include <DApplicationHelper>
#include <QGraphicsOpacityEffect>

class ImportTimeLineView : public DWidget
{
    Q_OBJECT
public:
    ImportTimeLineView();

    void updateStackedWidget();
public slots:
    void on_AddLabel(QString date,QString num);
    void on_DelLabel();
#if 1
    void on_MoveLabel(int y,QString date,QString num,QString choseText);
#endif
    void on_KeyEvent(int key);

protected:
    void resizeEvent(QResizeEvent *ev) override;

private:
    void initTimeLineViewWidget();
    void initConnections();
    void sigImprotPicsIntoThumbnailView();
    void getImageInfos();

    void initMainStackWidget();
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *e) override;
public:
    void updataLayout();
    void themeChangeSlot(DGuiApplicationHelper::ColorType themeType);

signals:
    void sigUpdatePicNum();

private:
    TimelineList *m_mainListWidget=nullptr;
    QLayout *m_mainLayout=nullptr;
    QList<QString> m_timelines;
    DWidget *m_dateItem=nullptr;
    DCommandLinkButton *pSuspensionChose;
    DWidget* pTimeLineViewWidget;
    ImportView* pImportView;
    QMap<ThumbnailListView*, QStringList> selpicQmap;
    int allnum;
    DLabel* m_pDate;
    DLabel* pNum_up;
    DLabel* pNum_dn;

    QList<ThumbnailListView*> m_allThumbnailListView;

    QGraphicsOpacityEffect * m_oe;
    QGraphicsOpacityEffect * m_oet;

public:
    int m_index;
    int m_selPicNum;
};

#endif // IMPORTTIMELINEVIEW_H