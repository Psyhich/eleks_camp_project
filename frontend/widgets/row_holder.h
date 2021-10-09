#ifndef MY_ROW_HOLDER_H
#define MY_ROW_HOLDER_H

#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QAbstractItemView>

class RowDisplay : public QWidget {
Q_OBJECT
private:
protected:
	inline void emitDeletePressed() { emit deletePressed(this); }
public:
	RowDisplay(QWidget *parrent = nullptr);

	virtual QVector<QString> getStrings() = 0;
	// Optional function to interact with this row
	virtual void setStrings(const QVector<QString>& stringsToSet){}

signals:
	void deletePressed(RowDisplay *row);
};

class RowHolder : public QScrollArea {
Q_OBJECT
private:
	QList<RowDisplay*> rows;
	QPushButton* addButton;
protected:
	inline const QList<RowDisplay*>& getRows() { return rows; }
	virtual RowDisplay* createRow() = 0;
public:
	RowHolder(QWidget *parrent = nullptr);
protected slots:
	void addRow();
private slots:
	void removeRow(RowDisplay *rowToRemove);
};

#endif // ROWHOLDER_H
