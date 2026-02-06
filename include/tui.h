#ifndef _TUI_H_
#define _TUI_H_

#include <stdbool.h>
#include <tui/definitions.h>
#include <tui/widget.h>


void tui_init(const char *name);
void tui_destroy(void);

void tui_set_content(TWidget *widget);

void tui_start(void);
void tui_stop(void);

void tui_connect_signal(const char *name, tsignal_cb cb);

#endif /* _TUI_H_ */
