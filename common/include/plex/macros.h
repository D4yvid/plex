#ifndef __PLEX_MACROS_H__
#define __PLEX_MACROS_H__

#define _CONCAT(x, y) x##y
#define _TOSTRING(x) #x

#define TOSTRING(x) _TOSTRING(x)
#define CONCAT(x, y) _CONCAT(TOSTRING(x), TOSTRING(y))

#endif /** __PLEX_MACROS_H__ */
