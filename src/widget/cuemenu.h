#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "track/cue.h"
#include "track/track.h"
#include "widget/wcolorpicker.h"

class CueMenu : public QWidget {
    Q_OBJECT
  public:
    CueMenu(QWidget* parent = nullptr);

    ~CueMenu() {
        delete m_pCueNumber;
        delete m_pCuePosition;
        delete m_pEditLabel;
        delete m_pColorPicker;
        delete m_pRemoveCue;
    }

    void setTrackAndCue(TrackPointer pTrack, CuePointer pCue);

    void useColorSet(PredefinedColorsRepresentation* pColorRepresentation) {
        if (m_pColorPicker != nullptr) {
            m_pColorPicker->useColorSet(pColorRepresentation);
        }
    }

    void popup(const QPoint& p, QAction* atAction = nullptr) {
        Q_UNUSED(atAction);
        qDebug() << "Showing menu at" << p;
        move(p);
        show();
    }

    void hide() {
        emit(aboutToHide());
        QWidget::hide();
    }

    void show() {
        emit(aboutToShow());
        QWidget::show();
    }

  signals:
    void aboutToHide();
    void aboutToShow();

  private slots:
    void slotEditLabel();
    void slotRemoveCue();
    void slotChangeCueColor(PredefinedColorPointer pColor);

  private:
    CuePointer m_pCue;
    TrackPointer m_pTrack;

    QLabel* m_pCueNumber;
    QLabel* m_pCuePosition;
    QLineEdit* m_pEditLabel;
    WColorPicker* m_pColorPicker;
    QPushButton* m_pRemoveCue;
};
