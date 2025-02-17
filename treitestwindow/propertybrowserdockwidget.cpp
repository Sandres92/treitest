#include "propertybrowserdockwidget.h"
#include <QDebug>

namespace trei
{
    PropertyBrowserDockWidget::PropertyBrowserDockWidget(const QString &title, QWidget *parent):QDockWidget(title, parent)
    {
        variantManager = new QtVariantPropertyManager();
        QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
        propertyBrowser = new QtTreePropertyBrowser();

        propertyBrowser->setFactoryForManager(variantManager, variantFactory);

        setWidget(propertyBrowser);
        setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
        hide();
    }

    PropertyBrowserDockWidget::~PropertyBrowserDockWidget()
    {
        delete propertyBrowser;
        delete variantManager;

        if(selectedObjectView)
        {
            selectedObjectView = nullptr;
        }
    }

    void PropertyBrowserDockWidget::showPropertyBrowser(ObjectView *objectView)
    {
        selectedObjectView = objectView;
        loadPropertyBrowser(objectView);
        show();
    }

    void PropertyBrowserDockWidget::hidePropertyBrowser()
    {
        hide();
        variantManager->clear();
        propertyBrowser->clear();
        disconnect(variantManagerConnection);
    }

    void PropertyBrowserDockWidget::loadPropertyBrowser(const ObjectView *objectView)
    {
        disconnect(variantManagerConnection);

        variantManager->clear();
        propertyBrowser->clear();

        const QMetaObject *metaObject = objectView->metaObject();
        const QMetaObject *objectViewMeta = &ObjectView::staticMetaObject;
        int firstPropertyIndex = objectViewMeta->propertyOffset();

        for (int i = firstPropertyIndex; i < metaObject->propertyCount(); ++i)
        {

            QMetaProperty property = metaObject->property(i);

            if (!property.isReadable())
            {
                continue;
            }

            QVariant value = property.read(objectView);

            if (property.userType() == qMetaTypeId<QVariantList>())
            {
                QtVariantProperty *arrayProp = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), property.name());

                QVariantList array = value.toList();

                for (int j = 0; j < array.size(); ++j)
                {
                    QString pointName = QString("%1").arg(j);
                    QVariant q = array[j];
                    QtVariantProperty *arrayElementProperty = variantManager->addProperty(q.type(), pointName);
                    arrayElementProperty->setValue(q);
                    arrayProp->addSubProperty(arrayElementProperty);
                }

                propertyBrowser->addProperty(arrayProp);
            }
            else
            {
                QtVariantProperty *prop = variantManager->addProperty(value.type(), property.name());
                prop->setValue(value);
                propertyBrowser->addProperty(prop);
            }
        }

        variantManagerConnection =
            connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                    this, SLOT(propertyBrowserValueChanged(QtProperty *, const QVariant &)));
    }

    void PropertyBrowserDockWidget::propertyBrowserValueChanged(QtProperty *property, const QVariant &value)
    {
        if (!selectedObjectView)
        {
            return;
        }

        const QMetaObject *metaObject = selectedObjectView->metaObject();

        int propertyIndex = metaObject->indexOfProperty(property->propertyName().toStdString().c_str());

        if (propertyIndex != -1)
        {
            QMetaProperty metaProperty = metaObject->property(propertyIndex);

            if (metaProperty.userType() == qMetaTypeId<QVariantList>())
            {

            }
            else
            {
                metaProperty.write(selectedObjectView, value);
            }
        }
    }

    void PropertyBrowserDockWidget::updatePosPropertyBrowser(const ObjectView *objectView)
    {
        QSet<QtProperty *> properties = variantManager->properties();
        QList<QtProperty *> posProperties;

        auto itPosx = std::find_if(properties.begin(), properties.end(),
                                   [](const QtProperty * prop)
                                   {
                                       return prop->propertyName() == "posx";
                                   });

        if (itPosx != properties.end())
        {
            QtProperty *foundProp = *itPosx;
            QVariant value(objectView->getPosx());

            variantManager->setValue(foundProp, value);
        }

        auto itPosy = std::find_if(properties.begin(), properties.end(),
                                   [](const QtProperty * prop)
                                   {
                                       return prop->propertyName() == "posy";
                                   });

        if (itPosy != properties.end())
        {
            QtProperty *foundProp = *itPosy;
            QVariant value(objectView->getPosy());

            variantManager->setValue(foundProp, value);
        }
    }
}
