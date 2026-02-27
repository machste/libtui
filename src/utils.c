#include <stdio.h>
#include <masc/math.h>
#include "utils_internal.h"


size_t tsize_to_cstr(TSize *s, char *cstr, size_t size)
{
    return snprintf(cstr, size, "%ix%i", s->h, s->w);
}

bool tsize_eq(TSize *self, TSize *other)
{
    return self->h == other->h && self->w == other->w;
}

size_t trect_to_cstr(TRect *r, char *cstr, size_t size)
{
    long len = 0;
    len += snprintf(cstr, size, "(%i,%i) ", r->y, r->x);
    len += tsize_to_cstr(r, cstr + len, max(0, size - len));
    return len;
}

bool rect_eq(TRect *self, TRect *other)
{
    return tsize_eq(self, other) \
            && self->x == other->x && self->y == other->y;
}

/* TUI Internal Utilities */

const cchar_t *tlinestyle_char(TLineStyle style, TAxis dir)
{
    static cchar_t def_char = { A_NORMAL, L" " };
    if (dir == TAXIS_Y) {
        if (style == TLINE_STYLE_SINGLE) {
            return WACS_VLINE;
        } else if (style == TLINE_STYLE_THICK) {
            return WACS_T_VLINE;
        } else if (style == TLINE_STYLE_DOUBLE) {
            return WACS_D_VLINE;
        }
    } else {
        if (style == TLINE_STYLE_SINGLE) {
            return WACS_HLINE;
        } else if (style == TLINE_STYLE_THICK) {
            return WACS_T_HLINE;
        } else if (style == TLINE_STYLE_DOUBLE) {
            return WACS_D_HLINE;
        }
    }
    return &def_char;
}
