#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <string.h>
#include <stdio.h>
#include <tui/mainlayout.h>


TMainLayout *tmainlayout_new(const char *title)
{
    TMainLayout *self = malloc(sizeof(TMainLayout));
    tmainlayout_init(self, title);
    return self;
}

void tmainlayout_init(TMainLayout *self, const char *title)
{
    object_init(self, TMainLayoutCls);
    twidget_init(self);
    ttitlebar_init(&self->title_bar, title);
    tstatusbar_init(&self->status_bar);
    self->center_widget = NULL;
}

void tmainlayout_vinit(TMainLayout *self, va_list va)
{
    const char *title = va_arg(va, const char *);
    tmainlayout_init(self, title);
}

void tmainlayout_destroy(TMainLayout *self)
{
    destroy(&self->status_bar);
    destroy(&self->title_bar);
    twidget_destroy(self);
}

void tmainlayout_delete(TMainLayout *self)
{
    tmainlayout_destroy(self);
    free(self);
}

void tmainlayout_set_center(TMainLayout *self, TWidget *widget)
{
    // Remove parent reference from previous center widget
    if (self->center_widget != NULL) {
        self->center_widget->parent = NULL;
    }
    self->center_widget = widget;
}

void tmainlayout_draw(TMainLayout *self)
{
    draw(&self->title_bar);
    if (self->center_widget != NULL) {
        draw(self->center_widget);
    }
    draw(&self->status_bar);
}

void tmainlayout_set_geometry(TMainLayout *self, TRect r)
{
    set_geometry(&self->title_bar, TRECT(r.y, r.x, 1, r.w));
    if (self->center_widget != NULL) {
        set_geometry(self->center_widget, TRECT(r.y + 1, r.x, r.h - 2, r.w));
    }
    set_geometry(&self->status_bar, TRECT(r.h - 1, r.x, 1, r.w));
}

static void _init_class(class *cls)
{
    cls->super = TWidgetCls;
}


static twidget_class _TMainLayoutCls = {
    .name = "TMainLayout",
    .size = sizeof(TMainLayout),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)tmainlayout_vinit,
    .init_copy = object_init_copy,
    .destroy = object_destroy,
    .cmp = (cmp_cb)object_cmp,
    .repr = (repr_cb)object_to_cstr,
    .to_cstr = (to_cstr_cb)twidget_to_cstr,
    // Widget Class
    .draw = (draw_cb)tmainlayout_draw,
    .set_geometry = (set_geometry_cb)tmainlayout_set_geometry
};

const twidget_class *TMainLayoutCls = &_TMainLayoutCls;