#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef DEBUG
#define debug_print(format, ...) printf(format, ## __VA_ARGS__);
#else
#define debug_print(format, ...)
#endif

#endif