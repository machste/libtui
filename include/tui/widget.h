#ifndef _TUI_WIDGET_H_
#define _TUI_WIDGET_H_

#include <masc/object.h>
#include <masc/map.h>
#include <tui/definitions.h>

typedef struct TWidget TWidget;

struct TWidget {
    Object;
    TRect geo;
    TWidget *parent;
    Map *signals;
};

typedef bool (*tsignal_cb)(TWidget *widget, void *data);


TWidget *twidget_new(void);
void twidget_init(TWidget *self);
void twidget_vinit(TWidget *self, va_list va);

void twidget_destroy(TWidget *self);
void twidget_delete(TWidget *self);

void twidget_draw(TWidget *self);
void twidget_set_geometry(TWidget *self, TRect r);

bool twidget_emit_singal(TWidget *self, const char *name, void *data);
void twidget_connect_signal(TWidget *self, const char *name, tsignal_cb cb);

size_t twidget_to_cstr(TWidget *self, char *cstr, size_t size);


/* TWidget Class Definitions */

typedef void (*draw_cb)(TWidget *self);
typedef void (*set_geometry_cb)(TWidget *self, TRect r);

typedef struct {
    class;
    draw_cb draw;
    set_geometry_cb set_geometry;
} twidget_class;


extern const twidget_class *TWidgetCls;


void draw(TWidget *self);
void set_geometry(TWidget *self, TRect r);

#endif /* _TUI_WIDGET_H_ */
