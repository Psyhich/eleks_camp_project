#ifndef SEARCHER_H
#define SEARCHER_H

#include <QSharedPointer>
#include "base_types.h"
#include <QTcpSocket>

namespace Searchers {

  class Searcher
  {
	public:
	  Searcher();
	  virtual QList<BaseTypes::Recipe* > getRecipes(BaseTypes::RequestQuery query) = 0;
	  virtual bool postRecipe(BaseTypes::Recipe *recipeToSend) = 0;

  };

  class OnlineSearcher : public Searcher{
	QTcpSocket socket;

	public:
	  OnlineSearcher(QString addressToQuery){
	  }
  };
}

#endif // SEARCHER_H
