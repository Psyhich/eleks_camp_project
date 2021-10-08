#include <QVBoxLayout>
#include <QComboBox>

#include "row_holder.h"

RowDisplay::RowDisplay(QWidget *parrent) : QWidget(parrent){ }

RowHolder::RowHolder(QWidget *parrent) : QScrollArea(parrent) {
	setWidgetResizable(true);
	setWidget(new QWidget());

	QVBoxLayout *mainLayout = new QVBoxLayout(widget());

	addButton = new QPushButton("+", widget());
	mainLayout->addWidget(addButton, 0, Qt::AlignmentFlag::AlignRight);
	widget()->setLayout(mainLayout);

	QObject::connect(addButton, &QPushButton::clicked, this, &RowHolder::addRow);
}

void RowHolder::addRow() {
  RowDisplay* newCreatedRow = createRow();
  newCreatedRow->setParent(widget());
  widget()->layout()->removeWidget(addButton);
  widget()->layout()->addWidget(newCreatedRow);
  widget()->layout()->addWidget(addButton);

  rows.append(newCreatedRow);
}

void RowHolder::removeRow(RowDisplay* rowToRemove) {
	widget()->layout()->removeWidget(rowToRemove);
	rowToRemove->deleteLater();
	rows.removeAll(rowToRemove);
}
