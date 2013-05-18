#include "FoliationManager.h"
#include "../fol/Foliation.h"
#include "../drawing/FoliationDrawingArea.h"
#include "foliationWidgets/SepSegmentSearchWidget.h"
#include "foliationWidgets/FoliationDataTableWidget.h"

#include <QMenu>

FoliationManager::FoliationManager(std::unique_ptr<balazs::Foliation> foliation, QObject *parent) :
    QObject(parent),
    pFoliation(std::move(foliation))
{
    pDrawingArea = new FoliationDrawingArea(*pFoliation);
    pFoliationDataTableWidget = new FoliationDataTableWidget(*pFoliation);
    pSepSegmentSearchWidget = new SepSegmentSearchWidget(*pFoliation);
    createViewMenu();

    connect(pSepSegmentSearchWidget, SIGNAL(drawSepSegment(const balazs::SeparatrixSegment*)),
            pDrawingArea, SLOT(drawSepSegment(const balazs::SeparatrixSegment*)));
}

FoliationManager::~FoliationManager() = default;


const balazs::Foliation& FoliationManager::foliation() const
{
    return *pFoliation;
}

SepSegmentSearchWidget *FoliationManager::sepSegmentSearchWidget() const
{
    return pSepSegmentSearchWidget;
}

FoliationDrawingArea *FoliationManager::drawingArea() const
{
    return pDrawingArea;
}

QMenu *FoliationManager::viewMenu() const
{
    return m_viewMenu;
}


FoliationDataTableWidget* FoliationManager::foliationDataTableWidget() const
{
    return pFoliationDataTableWidget;
}


void FoliationManager::createViewMenu()
{
    permutationLabelsAct = new QAction(tr("Show permutation"), this);
    lengthsLabelsAct = new QAction(tr("Show lengths"), this);
    coloredfillingAct = new QAction(tr("Use colored filling"), this);

    permutationLabelsAct->setCheckable(true);
    lengthsLabelsAct->setCheckable(true);
    coloredfillingAct->setCheckable(true);

    connect(permutationLabelsAct, SIGNAL(toggled(bool)), pDrawingArea, SLOT(setPermutationLabels(bool)));
    connect(lengthsLabelsAct, SIGNAL(toggled(bool)), pDrawingArea, SLOT(setLengthsLabels(bool)));
    connect(coloredfillingAct, SIGNAL(toggled(bool)), pDrawingArea, SLOT(setColoredFilling(bool)));

    permutationLabelsAct->setChecked(true);
    lengthsLabelsAct->setChecked(true);
    coloredfillingAct->setChecked(true);


    m_viewMenu = new QMenu(tr("View"));
    m_viewMenu->addAction(permutationLabelsAct);
    m_viewMenu->addAction(lengthsLabelsAct);
    m_viewMenu->addAction(coloredfillingAct);
}






