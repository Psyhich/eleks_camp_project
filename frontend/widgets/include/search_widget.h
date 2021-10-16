#ifndef MY_SEARCH_WIDGET_H
#define MY_SEARCH_WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>

class MySearchWidget : public QWidget {
	Q_OBJECT
private:
	QLineEdit *searchLine;
	QPushButton *searchButton;
	QToolButton *moreButton;

public:
	MySearchWidget(QWidget *parent = nullptr);
	QString getSearchSubstring();

signals:
	void searchButtonClicked();
	void moreButtonClicked(bool state);
};

#endif // MY_SEARCH_WIDGET_H
