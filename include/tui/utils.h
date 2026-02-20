#ifndef _TUI_UTILS_H_
#define _TUI_UTILS_H_

#include <stddef.h>
#include <stdbool.h>
#include <tui/definitions.h>


size_t tsize_to_cstr(TSize *s, char *cstr, size_t size);
bool tsize_eq(TSize *self, TSize *other);

size_t trect_to_cstr(TRect *r, char *cstr, size_t size);
bool rect_eq(TRect *self, TRect *other);


#endif /* _TUI_UTILS_H_ */
