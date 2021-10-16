#include "abstract_tab.h"
#include "tab_manager.h"

AbstractTab::AbstractTab(TabManager *parrent) : QWidget(parrent) {

}

TabManager *AbstractTab::parentWidget() const {
  // Looks scary but I don't want to store additional pointer
  return static_cast<TabManager *>(static_cast<const QWidget*>(this)->parentWidget());
}
