#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <tui/boxlayout.h>


TBoxLayout *tboxlayout_new(TBoxLayoutDirection dir)
{
    TBoxLayout *self = malloc(sizeof(TBoxLayout));
    tboxlayout_init(self, dir);
    return self;
}

void tboxlayout_init(TBoxLayout *self, TBoxLayoutDirection dir)
{
    object_init(self, TBoxLayoutCls);
    twidget_init(self);
    self->dir = dir;
    list_init(&self->children);
}

void tboxlayout_vinit(TBoxLayout *self, va_list va)
{
    TBoxLayoutDirection dir = va_arg(va, TBoxLayoutDirection);
    tboxlayout_init(self, dir);
}

void tboxlayout_destroy(TBoxLayout *self)
{
    list_destroy(&self->children);
    twidget_destroy(self);
}

void tboxlayout_delete(TBoxLayout *self)
{
    tboxlayout_destroy(self);
    free(self);
}

void tboxlayout_draw(TBoxLayout *self)
{
}

static void _init_class(class *cls)
{
    cls->super = TWidgetCls;
}


static twidget_class _TBoxLayoutCls = {
    .name = "TBoxLayout",
    .size = sizeof(TBoxLayout),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)tboxlayout_vinit,
    .init_copy = object_init_copy,
    .destroy = object_destroy,
    .cmp = (cmp_cb)object_cmp,
    .repr = (repr_cb)object_to_cstr,
    .to_cstr = (to_cstr_cb)twidget_to_cstr,
    // Widget Class
    .draw = (draw_cb)tboxlayout_draw,
    .set_geometry = (set_geometry_cb)twidget_set_geometry
};

const twidget_class *TBoxLayoutCls = &_TBoxLayoutCls;