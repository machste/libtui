#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <string.h>
#include <tui/titlebar.h>


TTitleBar *ttitlebar_new(const char *title)
{
    TTitleBar *self = malloc(sizeof(TTitleBar));
    ttitlebar_init(self, title);
    return self;
}

void ttitlebar_init(TTitleBar *self, const char *title)
{
    object_init(self, TTitleBarCls);
    twidget_init(self);
    self->title = strdup(title);
}

void ttitlebar_vinit(TTitleBar *self, va_list va)
{
    const char *title = va_arg(va, const char *);
    ttitlebar_init(self, title);
}

void ttitlebar_destroy(TTitleBar *self)
{
    twidget_destroy(self);
}

void ttitlebar_delete(TTitleBar *self)
{
    ttitlebar_destroy(self);
    free(self);
}

void ttitlebar_draw(TTitleBar *self)
{
    attron(A_REVERSE);
    mvprintw(self->geo.y, self->geo.x, self->title);
    hline(' ', self->geo.w);
    attroff(A_REVERSE);
}

static void _init_class(class *cls)
{
    cls->super = TWidgetCls;
}


static twidget_class _TTitleBarCls = {
    .name = "TTitleBar",
    .size = sizeof(TTitleBar),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)ttitlebar_vinit,
    .init_copy = object_init_copy,
    .destroy = object_destroy,
    .cmp = (cmp_cb)object_cmp,
    .repr = (repr_cb)object_to_cstr,
    .to_cstr = (to_cstr_cb)twidget_to_cstr,
    // Widget Class
    .draw = (draw_cb)ttitlebar_draw,
    .set_geometry = (set_geometry_cb)twidget_set_geometry
};

const twidget_class *TTitleBarCls = &_TTitleBarCls;