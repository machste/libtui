#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <string.h>
#include <stdio.h>
#include <masc/math.h>
#include <tui/label.h>


TLabel *tlabel_new(const char *text)
{
    TLabel *self = malloc(sizeof(TLabel));
    tlabel_init(self, text);
    return self;
}

void tlabel_init(TLabel *self, const char *text)
{
    object_init(self, TLabelCls);
    twidget_init(self);
    self->text = strdup(text);
}

void tlabel_vinit(TLabel *self, va_list va)
{
    char *text = (char *)va_arg(va, char *);
    tlabel_init(self, text);
}

void tlabel_destroy(TLabel *self)
{
    free(self->text);
    twidget_destroy(self);
}

void tlabel_delete(TLabel *self)
{
    tlabel_destroy(self);
    free(self);
}

const char *tlabel_text(TLabel *self)
{
    return self->text;
}

void tlabel_set_text(TLabel *self, const char *text)
{
    free(self->text);
    self->text = strdup(text);
}

void tlabel_draw(TLabel *self)
{
    mvprintw(self->geo.y, self->geo.x, self->text);
}

static int _cmp(const TLabel *self, const TLabel *other)
{
    return strcmp(self->text, other->text);
}

static size_t _to_cstr(TLabel *self, char *cstr, size_t size)
{
    long len = 0;
    len += twidget_to_cstr(self, cstr, size);
    len += snprintf(cstr + len, max(0, size - len), ", text: %s", self->text);

    return len;
}

static void _init_class(class *cls)
{
    cls->super = TWidgetCls;
}


static twidget_class _TLabelCls = {
    .name = "TLabel",
    .size = sizeof(TLabel),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)tlabel_vinit,
    .init_copy = object_init_copy,
    .destroy = object_destroy,
    .cmp = (cmp_cb)_cmp,
    .repr = (repr_cb)_to_cstr,
    .to_cstr = (to_cstr_cb)_to_cstr,
    // Widget Class
    .draw = (draw_cb)tlabel_draw,
    .set_geometry = twidget_set_geometry
};

const twidget_class *TLabelCls = &_TLabelCls;
