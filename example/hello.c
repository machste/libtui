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
    tui_init("My First TUI Application");
    tui_set_content(new(TLabel, "Hello World!"));
    tui_connect_signal("key-pressed", key_pressed_cb);
    tui_start();
    tui_destroy();
    return 0;
}
