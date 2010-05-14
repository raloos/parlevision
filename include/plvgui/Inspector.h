#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include <QObject>

#include "RefPtr.h"
#include "Types.h"

namespace plv {
    class Pin;
}

using namespace plv;

namespace plvgui {

    /** Interface for Inspectors that observe or monitor pins of a certain dataType.
      * Each implementation must register itself with the InspectorFactory
      * and implement the methods needed to render the datatype.
      */
    class Inspector : public QWidget
    {
        Q_OBJECT

    public:
        Inspector( QWidget* parent );
        virtual ~Inspector();

        /** Start inspecting this pin
          * Disconnects all previous connections
          */
        virtual void setPin(const plv::Pin* pin);

    public slots:
        virtual void newData( RefPtr<Data> data );

    };
}

#endif // INSPECTOR_H