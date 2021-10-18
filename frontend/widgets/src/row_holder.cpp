#include <QVBoxLayout>
#include <QComboBox>
#include <QScrollBar>

#include "row_holder.h"

RowDisplay::RowDisplay(QWidget *parrent) : QWidget(parrent){ }

RowHolder::RowHolder(QWidget *parrent) : QScrollArea(parrent) {
	setWidgetResizable(true);

	setWidget(new QWidget(this));
	QVBoxLayout *mainLayout = new QVBoxLayout(widget());

	addButton = new QPushButton("+", widget());
	mainLayout->addWidget(addButton, 1,
						  Qt::AlignRight | Qt::AlignBottom);

	widget()->setLayout(mainLayout);

	QObject::connect(addButton, &QPushButton::clicked, this, &RowHolder::addRow);
}

void RowHolder::addRow() {
  RowDisplay* newCreatedRow = createRow();
  newCreatedRow->setParent(widget());
  // Adding row to the end of all rows, but moving add button to the end
  widget()->layout()->removeWidget(addButton);
  widget()->layout()->addWidget(newCreatedRow);
  widget()->layout()->setAlignment(newCreatedRow, Qt::AlignTop);

  // Reading addButton with proper alignment
  widget()->layout()->addWidget(addButton);
  widget()->layout()->setAlignment(addButton,
							   Qt::AlignRight | Qt::AlignBottom);

  QObject::connect(newCreatedRow, &RowDisplay::deletePressed,
				   this, &RowHolder::removeRow);

  rows.append(newCreatedRow);

 verticalScrollBar()->setValue(verticalScrollBar()->maximum() + 1000);
}

void RowHolder::removeRow(RowDisplay* rowToRemove) {
	widget()->layout()->removeWidget(rowToRemove);
	rowToRemove->deleteLater();
	rows.removeAll(rowToRemove);
}
