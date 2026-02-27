#ifndef _TUI_SEPARATOR_H_
#define _TUI_SEPARATOR_H_

#include <tui/widget.h>


typedef struct {
    TWidget;
    TAxis dir;
    TLineStyle line_style;
} TSeparator;


extern const twidget_class *TSeparatorCls;


TSeparator *tseparator_new(TAxis dir, TLineStyle style);
void tseparator_init(TSeparator *self, TAxis dir, TLineStyle style);
void tseparator_vinit(TSeparator *self, va_list va);

void tseparator_destroy(TSeparator *self);
void tseparator_delete(TSeparator *self);

#endif /* _TUI_SEPARATOR_H_ */
