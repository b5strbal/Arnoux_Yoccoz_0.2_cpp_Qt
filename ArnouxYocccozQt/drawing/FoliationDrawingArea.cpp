#include "FoliationDrawingArea.h"
#include "../fol/Foliation.h"
#include "../scc/SeparatrixSegment.h"
#include <QPainter>
#include <QDebug>
//#include <QFont>

FoliationDrawingArea::FoliationDrawingArea(const balazs::Foliation &foliation, QWidget *parent) :
    QWidget(parent),
    m_foliation(foliation),
    pSepSegment(nullptr)
{
    permFontSize = lengthsFontSize = 10;
    setBackgroundRole(QPalette::Base);
    update();
}



void FoliationDrawingArea::setPermutationLabels(bool visible)
{
    permutationLabelsShown = visible;
    update();
}

void FoliationDrawingArea::setLengthsLabels(bool visible)
{
    lengthsLabelsShown = visible;
    update();
}

void FoliationDrawingArea::setColoredFilling(bool visible)
{
    coloredFillingShown = visible;
    update();
}

void FoliationDrawingArea::drawSepSegment(const balazs::SeparatrixSegment *pSegment)
{
    pSepSegment = pSegment;
    update();
}






void FoliationDrawingArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paint(painter, width(), height());
  //  painter.setRenderHint(QPainter::Antialiasing);


}

void FoliationDrawingArea::paint(QPainter &painter, int w, int h)
{
    painter.resetTransform();
    painter.translate(w / 10.0, h / 10.0);

    double folW = w * 8 / 10.0;
    double folH = h * 8 / 10.0;

    paintFilling(painter, folW, folH);
    paintFoliation(painter, folW, folH);
    paintLengthLabels(painter, folW, folH);
    paintPermutationLabels(painter, folW, folH);
    paintSepSegment(painter, folW, folH);
}


inline double heightOfSingularity(const balazs::Foliation& foliation, std::size_t sepIndex, int folH)
{
    return  folH * (foliation.indexOfSingularity()[sepIndex] + 1.0) / (foliation.numSingularities() + 1.0);
}




void FoliationDrawingArea::paintFoliation(QPainter &painter, int folW, int folH)
{
    painter.setPen(QPen(Qt::black, 0, Qt::SolidLine));
    painter.drawRect(0, 0, folW, folH);

    for(std::size_t i = 0; i < m_foliation.numIntervals(); i++){
        double singularityHeight = heightOfSingularity(m_foliation, i, folH);

        QPointF topPoint(folW * m_foliation.topDivPoints()[i], 0);
        QPointF middlePoint(folW * m_foliation.topDivPoints()[i], singularityHeight);
        QPointF bottomPoint(folW * m_foliation.topDivPoints()[i], folH);

        painter.setPen(QPen(Qt::black, 0, Qt::SolidLine));
        painter.drawLine(topPoint, middlePoint);
        painter.setPen(QPen(Qt::black, 0, Qt::DotLine));
        painter.drawLine(bottomPoint, middlePoint);

        painter.save();
        painter.setPen(QPen(Qt::black, 4));
        painter.drawPoint(middlePoint);
        painter.restore();
    }

    painter.setPen(QPen(Qt::black, 0, Qt::DashLine));
    for(std::size_t i = 0; i < m_foliation.numIntervals(); i++){
        QPointF topPoint(folW * m_foliation.bottomDivPoints()[i], folH);
        QPointF bottomPoint(folW * m_foliation.bottomDivPoints()[i], 1.05 * folH);
        painter.drawLine(topPoint, bottomPoint);
    }
}

void FoliationDrawingArea::paintLengthLabels(QPainter &painter, int folW, int folH)
{
    painter.setFont(QFont("Times", lengthsFontSize));

    if(lengthsLabelsShown){
        for(std::size_t i = 0; i < m_foliation.numIntervals(); i++){
            painter.drawText(QRectF(folW * m_foliation.topDivPoints()[i], 0,
                                    folW * m_foliation.intExchange().lengths()[i], folH),
                             Qt::AlignBottom | Qt::AlignHCenter,
                             QString::number(static_cast<double>(
                                                 m_foliation.intExchange().lengths()[i])));
        }
    }
}

void FoliationDrawingArea::paintPermutationLabels(QPainter &painter, int folW, int folH)
{
    painter.setFont(QFont("Times", permFontSize));

    if(permutationLabelsShown){
        for(std::size_t i = 0; i < m_foliation.numIntervals(); i++){
            painter.drawText(QRectF(folW * m_foliation.topDivPoints()[i], 2,
                                           folW * m_foliation.intExchange().lengths()[i], folH),
                             Qt::AlignTop | Qt::AlignHCenter,
                             QString::number(i));

            std::size_t bottomIndex = m_foliation.intExchange().permutationWithMinimalTwist()[i];
            QRectF rect;
            if(bottomIndex < m_foliation.numIntervals() - 1 ||
                    balazs::distanceBetween(m_foliation.bottomDivPoints()[bottomIndex], 1) >=
                    static_cast<long double>(m_foliation.intExchange().lengths()[i]) / 2){
                rect = QRectF(folW * m_foliation.bottomDivPoints()[bottomIndex], folH + 2,
                              folW * m_foliation.intExchange().lengths()[i], 10000);
            } else {
                rect = QRectF(folW * m_foliation.bottomDivPoints()[bottomIndex] - folW, folH + 2,
                              folW * m_foliation.intExchange().lengths()[i], 10000);
            }

            painter.drawText(rect, Qt::AlignTop | Qt::AlignHCenter, QString::number(i));
        }
    }
}

void FoliationDrawingArea::paintFilling(QPainter &painter, int folW, int folH)
{
    painter.setPen(Qt::NoPen);
    if(coloredFillingShown){
        // Qt::GlobalColor has predefinied colors, 7-18 are not white/black/grey.

        for(std::size_t i = 0; i < m_foliation.numIntervals(); i++){
            QBrush brush(Qt::GlobalColor(i % 12 + 7), Qt::Dense4Pattern);
            painter.fillRect(QRectF(folW * m_foliation.topDivPoints()[i], 0,
                                    folW * m_foliation.intExchange().lengths()[i], folH), brush);

            std::size_t bottomIndex = m_foliation.intExchange().permutationWithMinimalTwist()[i];
            if(bottomIndex < m_foliation.numIntervals() - 1){
                painter.fillRect(QRectF(folW * m_foliation.bottomDivPoints()[bottomIndex], folH,
                                    folW * m_foliation.intExchange().lengths()[i], 0.05 * folH), brush);
            } else {
                double firstPartWidth = folW * (1 - static_cast<double>(m_foliation.bottomDivPoints()[bottomIndex]));
                painter.fillRect(QRectF(folW * m_foliation.bottomDivPoints()[bottomIndex], folH,
                                    firstPartWidth, 0.05 * folH), brush);
                painter.fillRect(QRectF(0, folH,
                                    folW * m_foliation.intExchange().lengths()[i] - firstPartWidth, 0.05 * folH), brush);
            }

        }
    }
}



void FoliationDrawingArea::paintSepSegment(QPainter &painter, int folW, int folH)
{
    if(!pSepSegment) return;
    painter.setPen(QPen(Qt::blue, 2));

    // initializing the subsegment of depth 1
    balazs::SeparatrixSegment segment(pSepSegment->foliation(),
                                           pSepSegment->startingSingularity(), pSepSegment->vDirection());
    double shift = pSepSegment->side() == balazs::HDirection::Left ? -1.0 : 1.0;
    double singularityHeight = heightOfSingularity(m_foliation, segment.startingSingularity(), folH);
    double w = folW * static_cast<double>(m_foliation.topDivPoints()[segment.startingSingularity()]);

    if(segment.vDirection() == balazs::VDirection::Down){
        painter.drawLine(w + shift, singularityHeight, w + shift, folH);

        while(segment.depth() < pSepSegment->depth()){
            segment.lengthen();
            w = folW * static_cast<double>(segment.endpoint().number());
            painter.drawLine(w + shift, 0, w + shift, folH);
        }

    } else {
        painter.drawLine(w + shift, singularityHeight, w + shift, 0);
        while(segment.depth() < pSepSegment->depth()){
            w = folW * static_cast<double>(segment.endpoint().number());

            painter.drawLine(w + shift, 0, w + shift, folH);
            segment.lengthen();
        }
    }
}
