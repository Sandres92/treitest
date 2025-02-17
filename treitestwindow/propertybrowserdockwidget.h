#ifndef PROPERTYBROWSERDOCKWIDGET_H
#define PROPERTYBROWSERDOCKWIDGET_H

#include <qdockwidget.h>

#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>

#include "objects/objectview.h"
#include <qmetaobject.h>

namespace trei
{
    class PropertyBrowserDockWidget: public QDockWidget
    {
        Q_OBJECT

    public:
        explicit PropertyBrowserDockWidget(const QString &title, QWidget *parent);
        ~PropertyBrowserDockWidget();

        void showPropertyBrowser(ObjectView *objectView);
        void hidePropertyBrowser();

        void updatePosPropertyBrowser(const ObjectView *objectView);

    public slots:
        void propertyBrowserValueChanged(QtProperty *property, const QVariant &value);

    private:
        QtTreePropertyBrowser *propertyBrowser;
        QtVariantPropertyManager *variantManager;

        QMetaObject::Connection variantManagerConnection;

        void loadPropertyBrowser(const ObjectView *objectView);

        ObjectView *selectedObjectView = nullptr;
    };
}
#endif // PROPERTYBROWSERDOCKWIDGET_H
