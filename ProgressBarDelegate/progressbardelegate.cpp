#include "progressbardelegate.h"
#include <QApplication>

//static const int PROGRESS_STEP = 5;
//static const int PROGRESS_DELAY_MSEC = 100;
static const int MAX_PROGRESS_VALUE = 100;

static const int PROGRESS_BAR_HEIGHT_PX = 25;

ProgressBarDelegate::ProgressBarDelegate()
{

}


void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int progress = index.data().toInt();

    QStyleOptionProgressBar progressBarOption;
    QRect r = option.rect;
    r.setHeight( PROGRESS_BAR_HEIGHT_PX );
    r.moveCenter( option.rect.center() );
    progressBarOption.rect = r;
    progressBarOption.textAlignment = Qt::AlignCenter;
    progressBarOption.minimum = 0;
    progressBarOption.maximum = MAX_PROGRESS_VALUE;
    progressBarOption.progress = progress;
    progressBarOption.text = QString::number( progress ) + "%";
    progressBarOption.textVisible = true;

    QStyledItemDelegate::paint( painter, option, QModelIndex() );
    QApplication::style()->drawControl( QStyle::CE_ProgressBar, &progressBarOption, painter );
}
