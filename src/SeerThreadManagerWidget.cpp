#include "SeerThreadManagerWidget.h"
#include "SeerHelpPageWidget.h"
#include "QHContainerWidget.h"
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTextBrowser>
#include <QtGui/QIcon>
#include <QtCore/QFile>
#include <QtCore/QDebug>

SeerThreadManagerWidget::SeerThreadManagerWidget (QWidget* parent) : QWidget(parent) {

    // Initialize private data

    // Setup UI
    setupUi(this);

    // Setup the widgets
    tabWidget->setMovable(true);
    tabWidget->setTabsClosable(false);

    _threadFramesBrowserWidget = new SeerThreadFramesBrowserWidget(this);
    _threadIdsBrowserWidget    = new SeerThreadIdsBrowserWidget(this);
    _threadGroupsBrowserWidget = new SeerThreadGroupsBrowserWidget(this);

    tabWidget->addTab(_threadFramesBrowserWidget, "Frames");
    tabWidget->addTab(_threadIdsBrowserWidget,    "Ids");
    tabWidget->addTab(_threadGroupsBrowserWidget, "Groups");

    QToolButton* refreshToolButton = new QToolButton(tabWidget);
    refreshToolButton->setIcon(QIcon(":/seer/resources/RelaxLightIcons/view-refresh.svg"));
    refreshToolButton->setToolTip("Refresh the thread information.");

    QToolButton* helpToolButton = new QToolButton(tabWidget);
    helpToolButton->setIcon(QIcon(":/seer/resources/RelaxLightIcons/help-about.svg"));
    helpToolButton->setToolTip("Help on thread information.");

    QHContainerWidget* hcontainer = new QHContainerWidget(this);
    hcontainer->setSpacing(3);
    hcontainer->addWidget(refreshToolButton);
    hcontainer->addWidget(helpToolButton);

    tabWidget->setCornerWidget(hcontainer, Qt::TopRightCorner);

    // Connect things.
    QObject::connect(refreshToolButton,        &QToolButton::clicked,                                   this,  &SeerThreadManagerWidget::handleRefreshToolButtonClicked);
    QObject::connect(helpToolButton,           &QToolButton::clicked,                                   this,  &SeerThreadManagerWidget::handleHelpToolButtonClicked);
    QObject::connect(schedulerLockingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),     this,  &SeerThreadManagerWidget::handleSchedulerLockingComboBox);
    QObject::connect(scheduleMultipleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),     this,  &SeerThreadManagerWidget::handleScheduleMultipleComboBox);
    QObject::connect(forkFollowsComboBox,      QOverload<int>::of(&QComboBox::currentIndexChanged),     this,  &SeerThreadManagerWidget::handleForkFollowComboBox);
}

SeerThreadManagerWidget::~SeerThreadManagerWidget () {
}

SeerThreadFramesBrowserWidget* SeerThreadManagerWidget::threadFramesBrowserWidget () {
    return _threadFramesBrowserWidget;
}

SeerThreadIdsBrowserWidget* SeerThreadManagerWidget::threadIdsBrowserWidget () {
    return _threadIdsBrowserWidget;
}

SeerThreadGroupsBrowserWidget* SeerThreadManagerWidget::threadGroupsBrowserWidget () {
    return _threadGroupsBrowserWidget;
}

void SeerThreadManagerWidget::setSchedulerLockingMode (const QString& mode) {

    schedulerLockingComboBox->setCurrentText(mode);
}

QString SeerThreadManagerWidget::schedulerLockingMode () const {

    return schedulerLockingComboBox->currentText();
}

void SeerThreadManagerWidget::setScheduleMultipleMode (const QString& mode) {

    scheduleMultipleComboBox->setCurrentText(mode);
}

QString SeerThreadManagerWidget::scheduleMultipleMode () const {

    return scheduleMultipleComboBox->currentText();
}

void SeerThreadManagerWidget::setForkFollowsMode (const QString& mode) {

    forkFollowsComboBox->setCurrentText(mode);
}

QString SeerThreadManagerWidget::forkFollowsMode () const {

    return forkFollowsComboBox->currentText();
}

void SeerThreadManagerWidget::handleRefreshToolButtonClicked () {

    threadFramesBrowserWidget()->refresh();
    threadIdsBrowserWidget()->refresh();
    threadGroupsBrowserWidget()->refresh();
}

void SeerThreadManagerWidget::handleHelpToolButtonClicked () {

    SeerHelpPageWidget* help = new SeerHelpPageWidget;
    help->loadFile(":/seer/resources/help/ThreadProcessInfoBrowser.md");
    help->show();
}

void SeerThreadManagerWidget::handleSchedulerLockingComboBox (int index) {

    Q_UNUSED(index);

    emit schedulerLockingModeChanged(schedulerLockingComboBox->currentText());
}

void SeerThreadManagerWidget::handleScheduleMultipleComboBox (int index) {

    Q_UNUSED(index);

    emit scheduleMultipleModeChanged(scheduleMultipleComboBox->currentText());
}

void SeerThreadManagerWidget::handleForkFollowComboBox (int index) {

    Q_UNUSED(index);

    emit forkFollowsModeChanged(forkFollowsComboBox->currentText());
}

