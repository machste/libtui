#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <tui/statusbar.h>


TStatusBar *tstatusbar_new(void)
{
    TStatusBar *self = malloc(sizeof(TStatusBar));
    tstatusbar_init(self);
    return self;
}

void tstatusbar_init(TStatusBar *self)
{
    object_init(self, TStatusBarCls);
    twidget_init(self);
}

void tstatusbar_vinit(TStatusBar *self, va_list va)
{
    tstatusbar_init(self);
}

void tstatusbar_destroy(TStatusBar *self)
{
    twidget_destroy(self);
}

void tstatusbar_delete(TStatusBar *self)
{
    tstatusbar_destroy(self);
    free(self);
}

void tstatusbar_draw(TStatusBar *self)
{
    TSize s = twidget_size(self);
    wclear(self->win);
    wattron(self->win, A_REVERSE);
    mvwhline(self->win, 0, 0, ' ', s.w);
    wattroff(self->win, A_REVERSE);
    wnoutrefresh(self->win);
}

static void _init_class(class *cls)
{
    cls->super = TWidgetCls;
}


static twidget_class _TStatusBarCls = {
    .name = "TStatusBar",
    .size = sizeof(TStatusBar),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)tstatusbar_vinit,
    .init_copy = object_init_copy,
    .destroy = object_destroy,
    .cmp = (cmp_cb)object_cmp,
    .repr = (repr_cb)object_to_cstr,
    .to_cstr = (to_cstr_cb)twidget_to_cstr,
    // Widget Class
    .draw = (draw_cb)tstatusbar_draw,
    .set_geometry = (set_geometry_cb)twidget_set_geometry
};

const twidget_class *TStatusBarCls = &_TStatusBarCls;