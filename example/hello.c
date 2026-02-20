#include <masc.h>
#include <tui.h>
#include <tui/label.h>


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
    // Initialise a TUI Application
    tui_init("My First TUI Application");
    // Create TUI Label and align its test to the center
    TLabel *hello = new(TLabel, "Hello World!");
    hello->align_x = TALIGN_CENTER;
    hello->align_y = TALIGN_CENTER;
    // Set the content of the main layout
    tui_set_content(hello);
    // Register a signal handler for pressed keys
    tui_connect_signal("key-pressed", key_pressed_cb);
    // Start the TUI application
    tui_start();
    tui_destroy();
    return 0;
}
