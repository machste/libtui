#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <masc/pointer.h>
#include <masc/math.h>
#include <tui/widget.h>


TWidget *twidget_new(void)
{
    TWidget *self = malloc(sizeof(TWidget));
    twidget_init(self);
    return self;
}

void twidget_init(TWidget *self)
{
    self->geo = (TRect){ .y = 0, .x = 0, .h = 0, .w = 0 };
    self->parent = NULL;
    self->signals = NULL;
}

void twidget_vinit(TWidget *self, va_list va)
{
    twidget_init(self);
}

void twidget_destroy(TWidget *self)
{
    map_delete(self->signals);
}


void twidget_delete(TWidget *self)
{
    twidget_destroy(self);
    free(self);
}

void twidget_draw(TWidget *self)
{
    mvprintw(self->geo.y, self->geo.x, "<%s>", name_of(self));
}


void twidget_set_geometry(TWidget *self, TRect r)
{
    self->geo = r;
}

bool twidget_emit_singal(TWidget *self, const char *name, void *data)
{
    bool sig_handled = false;
    if (self->signals == NULL) {
        return sig_handled;
    }
    // Check if there are signal handlers registerd for the given name.
    List *signal_cbs = map_get(self->signals, name);
    if (signal_cbs != NULL) {
        // Call all connected signal handlers
        Iter i = init(Iter, signal_cbs);
        for (Pointer *p = next(&i); p != NULL && !sig_handled; p = next(&i)) {
            if (p->ptr == NULL) {
                continue;
            }
            tsignal_cb cb = p->ptr;
            sig_handled = cb(self, data);
        }
        destroy(&i);
    }
    // If signal was not handled ...
    if (!sig_handled && self->parent != NULL) {
        // ... propagate signal to parent widget.
        return twidget_emit_singal(self->parent, name, data);
    }
    return sig_handled;
}

void twidget_connect_signal(TWidget *self, const char *name, tsignal_cb cb)
{
    List *signal_cbs = NULL;
    // If needed, create the signal handler map.
    if (self->signals == NULL) {
        self->signals = map_new();
    } else {
        signal_cbs = map_get(self->signals, name);
    }
    // If needed, create a signal handler list.
    if (signal_cbs == NULL) {
        signal_cbs = list_new();
        map_set(self->signals, name, signal_cbs);
    }
    list_append(signal_cbs, pointer_new(cb));
}

static size_t tsize_to_cstr(TSize *s, char *cstr, size_t size)
{
    return snprintf(cstr, size, "%ix%i", s->h, s->w);
}

static size_t trect_to_cstr(TRect *r, char *cstr, size_t size)
{
    long len = 0;
    len += snprintf(cstr, size, "(%i,%i) ", r->y, r->x);
    len += tsize_to_cstr(r, cstr + len, max(0, size - len));
    return len;
}

size_t twidget_to_cstr(TWidget *self, char *cstr, size_t size)
{
    long len = 0;
    len += snprintf(cstr, size, "%s ", name_of(self));
    len += trect_to_cstr(&self->geo, cstr + len, max(0, size - len));
    return len;
}


static const twidget_class *_class_of(const TWidget *self)
{
    if (isinstance(self, TWidget)) {
        return (twidget_class *)self->cls;
    } else {
        return NULL;
    }
}

void draw(TWidget *self)
{
    const twidget_class *wcls = _class_of(self);
    if (wcls == NULL) {
        return;
    }
    wcls->draw(self);
}

void set_geometry(TWidget *self, TRect r)
{
    const twidget_class *wcls = _class_of(self);
    if (wcls == NULL) {
        return;
    }
    wcls->set_geometry(self, r);
}

static void _init_class(class *cls)
{
    cls->super = ObjectCls;
}


static twidget_class _TWidgetCls = {
    .name = "TWidget",
    .size = sizeof(TWidget),
    .super = NULL,
    .init_class = _init_class,
    .vinit = (vinit_cb)twidget_vinit,
    .init_copy = (init_copy_cb)object_init_copy,
    .destroy = (destroy_cb)twidget_destroy,
    .cmp = (cmp_cb)object_cmp,
    .repr = (repr_cb)object_to_cstr,
    .to_cstr = (to_cstr_cb)twidget_to_cstr,
    // Widget Class
    .draw = twidget_draw,
    .set_geometry = twidget_set_geometry
};

const twidget_class *TWidgetCls = &_TWidgetCls;
