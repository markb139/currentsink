#ifndef __DBG_H__
#define __DBG_H__

#include "stdio.h"

#define _DBG_ENABLED_ 1

#if _DBG_ENABLED_
#define _DBG_PRINT(_A) printf(_A);
#define _DBG_PRINT2(_A,_B) printf(_A, _B);
#define _DBG_PRINT3(_A,_B, _C) printf(_A, _B, _C);
#else
#define _DBG_PRINT(_A) {}
#define _DBG_PRINT2(_A,_B) {}
#define _DBG_PRINT3(_A,_B, _C) {}
#endif

#endif