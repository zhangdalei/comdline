#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef DEBUG
#define debug_print(arg...) printf(arg);
#else
#define debug_print(arg...)
#endif

#endif