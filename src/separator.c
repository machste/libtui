#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <string.h>
#include <masc/math.h>
#include <tui/separator.h>
#include "utils_internal.h"


TSeparator *tseparator_new(TAxis dir, TLineStyle style)
{
    TSeparator *self = malloc(sizeof(TSeparator));
    tseparator_init(self, dir, style);
    return self;
}

void tseparator_init(TSeparator *self, TAxis dir, TLineStyle style)
{
    object_init(self, TSeparatorCls);
    twidget_init(self);
    self->dir = dir;
    self->line_style = style;
}

void tseparator_vinit(TSeparator *self, va_list va)
{
    TAxis dir = va_arg(va, TAxis);
    TLineStyle style = va_arg(va, TLineStyle);
    tseparator_init(self, dir, style);
}

void tseparator_destroy(TSeparator *self)
{
    twidget_destroy(self);
}

void tseparator_delete(TSeparator *self)
{
    tseparator_destroy(self);
    free(self);
}

void tseparator_draw(TSeparator *self)
{
    TSize s = twidget_size(self);
    const cchar_t *wch = tlinestyle_char(self->line_style, self->dir);
    wclear(self->win);
    if (self->dir == TAXIS_X) {
        // Draw a horizontal line
        mvwhline_set(self->win, max(s.h, 1) / 2, 1, wch, s.w - 2);
    } else {
        // Draw a vertial line
        mvwvline_set(self->win, 1, max(s.w, 1) / 2, wch, s.h - 2);
    }
    wnoutrefresh(self->win);
}

static void _init_class(class *cls)
{
    cls->super = TWidgetCls;
}


static twidget_class _TSeparatorCls = {
    .name = "TSeparator",
    .size = sizeof(TSeparator),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)tseparator_vinit,
    .init_copy = object_init_copy,
    .destroy = object_destroy,
    .cmp = (cmp_cb)object_cmp,
    .repr = (repr_cb)object_to_cstr,
    .to_cstr = (to_cstr_cb)twidget_to_cstr,
    // Widget Class
    .draw = (draw_cb)tseparator_draw,
    .set_geometry = (set_geometry_cb)twidget_set_geometry
};

const twidget_class *TSeparatorCls = &_TSeparatorCls;