#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QMap>
#include <DFileDialog>
#include <QTestEventList>
#include <QObject>
#include <QDialog>
#include <QStringList>
#include <DSearchEdit>

#define private public
#define protected public

#include "mainwindow.h"
#include "albumcreatedialog.h"
#include "test_qtestDefine.h"
#include "imginfodialog.h"
#include <stub-tool/cpp-stub/stub.h>
#include <stub-tool/stub-ext/stubext.h>

TEST(AlbumLeftTabItem, func_test)
{
    TEST_CASE_NAME("func_test")
    qDebug() << "AlbumLeftTabItem func_test count = " << count_testDefine++;
    MainWindow *w = dApp->getMainWindow();
    w->allPicBtnClicked();
    QTest::qWait(500);
    QString str = "hello";
    QString strType = "world";
    AlbumLeftTabItem *leftItem = new AlbumLeftTabItem(str, strType);
    leftItem->initUI();
    leftItem->unMountBtnClicked();
    leftItem->editAlbumEdit();
    leftItem->setExternalDevicesMountPath(str);
    leftItem->getalbumname();
    QTest::qWait(500);
}

TEST(AlbumLeftTabItem, onCheckNameValid_test)
{
    TEST_CASE_NAME("onCheckNameValid_test")
    qDebug() << "AlbumLeftTabItem onCheckNameValid_test count = " << count_testDefine++;
    MainWindow *w = dApp->getMainWindow();
    w->allPicBtnClicked();
    QTest::qWait(500);

    QString str = "hello";
    QString strType = "world";
    AlbumLeftTabItem *leftItem1 = new AlbumLeftTabItem(str, strType);
    leftItem1->initUI();
    leftItem1->m_opeMode = 1;
    leftItem1->onCheckNameValid();
    QTest::qWait(50);

    leftItem1->m_opeMode = 0;
    leftItem1->onCheckNameValid();
    QTest::qWait(500);
}

//

TEST(AlbumLeftTabItem, oriAlbumStatus_test)
{
    TEST_CASE_NAME("oriAlbumStatus_test")
    qDebug() << "AlbumLeftTabItem oriAlbumStatus_test count = " << count_testDefine++;
    MainWindow *w = dApp->getMainWindow();
    w->allPicBtnClicked();
    QTest::qWait(500);

    QString str = "hello";
    QString strType = "world";
    AlbumLeftTabItem *leftItem2 = new AlbumLeftTabItem(str, strType);
    leftItem2->initUI();

    int i = 0;
    stub_ext::StubExt stu;
    stu.set_lamda(ADDR(DGuiApplicationHelper, themeType), [i]() {
        if (i == 0)
            return DGuiApplicationHelper::LightType;
        else
            return DGuiApplicationHelper::DarkType;
    });

    for (i = 0; i < 2; i++) {
        leftItem2->m_albumTypeStr = ALBUM_PATHTYPE_BY_PHONE;
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);

        leftItem2->m_albumTypeStr = ALBUM_PATHTYPE_BY_U;
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);

        leftItem2->m_albumTypeStr = COMMON_STR_CUSTOM;
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);

        leftItem2->m_albumTypeStr = COMMON_STR_RECENT_IMPORTED;
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);

        leftItem2->m_albumTypeStr = COMMON_STR_TRASH;
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);

        leftItem2->m_albumTypeStr = COMMON_STR_FAVORITES;
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);

        leftItem2->m_albumTypeStr = "no";
        leftItem2->oriAlbumStatus();
        QTest::qWait(50);
    }
}

//
TEST(AlbumLeftTabItem, newAlbumStatus_test)
{
    TEST_CASE_NAME("newAlbumStatus_test")
    qDebug() << "AlbumLeftTabItem newAlbumStatus_test count = " << count_testDefine++;
    MainWindow *w = dApp->getMainWindow();
    w->allPicBtnClicked();
    QTest::qWait(500);

    QString str = "hello";
    QString strType = "world";
    AlbumLeftTabItem *leftItem3 = new AlbumLeftTabItem(str, strType);
    leftItem3->initUI();

    leftItem3->m_albumTypeStr = ALBUM_PATHTYPE_BY_PHONE;
    leftItem3->newAlbumStatus();
    QTest::qWait(50);

    leftItem3->m_albumTypeStr = ALBUM_PATHTYPE_BY_U;
    leftItem3->newAlbumStatus();
    QTest::qWait(50);

    leftItem3->m_albumTypeStr = COMMON_STR_CUSTOM;
    leftItem3->newAlbumStatus();
    QTest::qWait(50);

    leftItem3->m_albumTypeStr = COMMON_STR_RECENT_IMPORTED;
    leftItem3->newAlbumStatus();
    QTest::qWait(50);

    leftItem3->m_albumTypeStr = COMMON_STR_TRASH;
    leftItem3->newAlbumStatus();
    QTest::qWait(50);

    leftItem3->m_albumTypeStr = COMMON_STR_FAVORITES;
    leftItem3->newAlbumStatus();
    QTest::qWait(50);

    leftItem3->m_albumTypeStr = "no";
    leftItem3->newAlbumStatus();
    QTest::qWait(50);
}
