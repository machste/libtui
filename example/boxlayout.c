#include <masc.h>
#include <tui.h>
#include <tui/label.h>
#include <tui/boxlayout.h>


static bool key_pressed_cb(TWidget *widget, void *data)
{
    int key = *(int *)data;
    if (key == 'q' || key == 'Q' || key == TKEY_ESC) {
        tui_stop();
    }
    return true;
}

int main(int argc, char *argv[])
{
    log_init(LOG_DEBUG);
    log_add_file("boxlayout.log");
    // Initialise a TUI Application
    tui_init("TUI Example - Box Layout");
    // Create a vertial and horizontal box layout with labels as content
    TBoxLayout *vlayout = new(TBoxLayout, TBOX_LAYOUT_DIR_VERTIAL);
    TBoxLayout *row1 = new(TBoxLayout, TBOX_LAYOUT_DIR_HORIZONTAL);
    tboxlayout_add(row1, new(TLabel, "(1, 1)"));
    tboxlayout_add(row1, new(TLabel, "(1, 2)"));
    tboxlayout_add(row1, new(TLabel, "(1, 3)"));
    tboxlayout_add(vlayout, row1);
    tboxlayout_add(vlayout, new(TLabel, "(2, 1)"));
    TBoxLayout *row3 = new(TBoxLayout, TBOX_LAYOUT_DIR_HORIZONTAL);
    tboxlayout_add(row3, new(TLabel, "(3, 1)"));
    tboxlayout_add(row3, new(TLabel, "(3, 2)"));
    tboxlayout_add(vlayout, row3);
    // Set the content of the main layout
    tui_set_content(vlayout);
    // Register a signal handler for pressed keys
    tui_connect_signal("key-pressed", key_pressed_cb);
    // Start the TUI application
    tui_start();
    // Cleanup after TUI application has been stopped
    tui_destroy();
    return 0;
}
