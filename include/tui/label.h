#ifndef _TUI_LABEL_H_
#define _TUI_LABEL_H_

#include <tui/widget.h>


typedef struct TLabel {
    TWidget;
    char *text;
    TAlign align_x;
    TAlign align_y;
} TLabel;


extern const twidget_class *TLabelCls;


TLabel *tlabel_new(const char *text);
void tlabel_init(TLabel *self, const char *text);
void tlabel_vinit(TLabel *self, va_list va);

void tlabel_delete(TLabel *self);

const char *tlabel_text(TLabel *self);
void tlabel_set_text(TLabel *self, const char *text);

void tlabel_draw(TLabel *self);
void tlabel_geometry(TLabel *self, TRect r);

#endif /* _TUI_LABEL_H_ */
