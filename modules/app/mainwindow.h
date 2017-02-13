#ifndef mainwindow_h
#define mainwindow_h

#include <cmath>
#include <iostream>
#include <fstream>

#include <QDialog>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include <QScopedPointer>
#include <QShortcut>
#include <QTime>
#include <QTimer>

#include "core.h"

#include "dialogannotation.h"
#include "framebaseddata.h"
#include "qboundingbox.h"
#include "qframebasedtablemodel.h"
#include "videomanager.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QScopedPointer<Ui::MainWindow> ui;

    QAction *crta = NULL;
    QAction *crtb = NULL;
    QAction *crte = NULL;
    QAction *crtf = NULL;
    QAction *crti = NULL;
    QAction *crto = NULL;
    QAction *crtw = NULL;

    bool loaded;
    bool playing;
    bool frameBasedIsEnable;
    double totalFrames;
    int speed;

    QImage frameQImage;
    QString core_path;
    QTimer *playerTime = NULL;
    QTimer *saveTimer = NULL;

    Core *singleton = NULL;

    DialogAnnotation *annotationDialog = NULL;

    QBoundingBox *frameScene = NULL;
    QFrameBasedTableModel *tableModel = NULL;
    QGraphicsRectItem *rectangle = NULL;

    QString nome;
    int InitFrame;
    int EndFrame;

    QStringListModel *categoryModel = NULL;
    QStringListModel *labelModel = NULL;

    VideoManager *manager = NULL;

    // FrameBased:
    int frameId, indexId;
    mode manipulation;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    QString videopath;
    void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;
    void jumpTo(int frame);
    int getIniFrameValue();
    int getEndFrameValue();
    QString getInfoValue();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void enableWidgets(const bool _enable);
    void enableFrameBased(const bool _enable);
    void connectSignalSlots();
    void setShortcuts();
    void setTableModel();

    bool isPlaying();
    void isPlaying(const bool _enable);

    void changeSpeed(const int _speed);
    void pauseVideo();
    void playVideo();
    void stopVideo();
    void updateFrame();
    void updateFrame(const int _frameId);
    void restoreJson();

    // FrameBased:
    void initializeComboboxes();
    void initializeComboboxes(const QString _category);
    void enableDisableButtonBox();

public slots:
    void slot_Fshortcut();
    void slot_Ashortcut();
    void slot_Oshortcut();
    void slot_Ishortcut();
    void slot_Bshortcut();
    void slot_Eshortcut();
    void slot_Wshortcut();

    void slot_displayFrame(const QImage _frame);
    void slot_openFile();
    void slot_backupJson();
    void slot_importJson();
    void slot_importProgressBar();
    void slot_exportJson();
    void slot_closeApplitacion();
    void slot_openAttributes();
    void slot_slideVideo(int _frameId);

    void slot_playButtonPressed();
    void slot_rewindButtonPressed();
    void slot_rewindButtonPressed(const int _frameId);
    void slot_backButtonPressed();
    void slot_backButtonPressed(const int _frameId);
    void slot_forwardButtonPressed();
    void slot_forwardButtonPressed(const int _frameId);
    void slot_fastfButtonPressed();
    void slot_fastfButtonPressed(const int _frameId);
    void slot_stopButtonPressed();

    void slot_spinBoxSpeedValueChanged(int _value);
    void slot_tableviewFrameSingleClicked(const QModelIndex _index);
    void slot_tableViewFrameDoubleClicked(const QModelIndex _index);

    void slot_keepVideoRunning();
    void slot_viewFrameContextMenu(const QPoint &_point);
    void slot_viewFrameNewBoxMenu();
    void slot_viewFrameNewFrameMenu();
    void slot_viewFrameRemoveBoxMenu();
    void slot_tableViewContextMenu(const QPoint &_point);
    void slot_tableViewChangeAnnotation();
    void slot_tableViewRemoveAnnotation();

    void slot_frameBasedInsertAccepted(const FrameBasedData _data);
    void slot_frameBasedAlterAccepted(const FrameBasedData _data, const int _index);

    void slot_addBoundingBoxToCore(const Rect _box);
    void slot_resizeFrame();

    void slot_on_sectionClicked(int _index);

    // FrameBased:
    void slot_buttonBoxAccepted();
    void slot_buttonBoxRejected();
    void slot_lineEditInfoChanged();
    void slot_spinBoxValueChanged();

    void slot_initializeDialog();
    void slot_initializeDialog(const QModelIndex _index);
    void slot_comboBoxCategoryActivated(const QString &_text);

signals:
    void signal_drawFrameBboxes(const Frame _frame);
    void signal_sortTable(int);

    // FrameBased:
    void signal_buttonBoxAccepted();
    void signal_frameBasedInsertAccepted(const FrameBasedData _data);
    void signal_frameBasedAlterAccepted(const FrameBasedData _data, const int _index);
    void signal_frameBasedRejected();
};

#endif
