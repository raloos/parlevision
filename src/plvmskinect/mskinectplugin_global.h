#ifndef PLV_MSKINECT_PLUGIN_GLOBAL_H
#define PLV_MSKINECT_PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MSKINECT_PLUGIN_LIBRARY)
#  define MSKINECT_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define MSKINECT_PLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // PLV_MSKINECT_PLUGIN_GLOBAL_H
