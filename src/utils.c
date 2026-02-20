#include <stdio.h>
#include <masc/math.h>
#include <tui/utils.h>


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

