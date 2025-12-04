#pragma once

#include <QtCore/qglobal.h>

#if defined(SHAPE_CORE_LIBRARY)
#  define SHAPE_CORE_EXPORT Q_DECL_EXPORT
#else
#  define SHAPE_CORE_EXPORT Q_DECL_IMPORT
#endif
