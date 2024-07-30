#ifndef LOOKUPBUTTON_H
#define LOOKUPBUTTON_H

#include <QListWidget>


class LookupButton : public QListWidgetItem {
public:
    int index;
    LookupButton(QString title, int index) : index(index), QListWidgetItem(title, nullptr, QListWidgetItem::UserType) {
        QListWidgetItem::setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
};

#endif // LOOKUPBUTTON_H
