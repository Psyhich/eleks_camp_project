#ifndef RECIPE_ITEM_MODEL_H
#define RECIPE_ITEM_MODEL_H

#include "base_types.h"
#include <QAbstractItemModel>
#include <QObject>

#define MODEL_NAME_COLUMN 0         // (QString)
#define MODEL_ID_COLUMN 1           // (int)
#define MODEL_TAGS_COLUMN 2         // (QList<QString>)
#define MODEL_INGREDIENTS_COLUMN 3  // (QMap<QString, int>)
#define MODEL_CALORIES_COLUMN 4     // (int)
#define MODEL_WEIGHT_COLUMN 5       // (int)
#define MODEL_MIN_PORTIONS_COLUMN 6 // (int)
#define MODEL_TEXT_COLUMN 7         // (QString)
#define MODEL_PRESENTATION_COLUMN 8 // (QString)

class RecipesListModel : public QAbstractListModel {
  QList<QSharedPointer<BaseTypes::Recipe>> recipes;

public:
  explicit RecipesListModel(QList<QSharedPointer<BaseTypes::Recipe>> recipes,
                            QObject *parent = nullptr);

  // QAbstractItemModel interface
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
};

#endif // RECIPE_ITEM_MODEL_H
