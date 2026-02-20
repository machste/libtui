#include <masc.h>
#include <tui.h>
#include <tui/label.h>


typedef struct {
    const char *text;
    TAlign y;
    TAlign x;
} AnimationFrame;


static const char *hello_msg = "Press <SPACE> to start animation.";
static MlTimer animation_timer;
static int animation_interval = 500;
static int animation_frame = 0;

static AnimationFrame frames[] = {
    { .text = "Top Left", .y = TALIGN_START, .x = TALIGN_START },
    { .text = "Top Center", .y = TALIGN_START, .x = TALIGN_CENTER },
    { .text = "Top Right", .y = TALIGN_START, .x = TALIGN_END },
    { .text = "Middle Left", .y = TALIGN_CENTER, .x = TALIGN_START },
    { .text = "Middle Center", .y = TALIGN_CENTER, .x = TALIGN_CENTER },
    { .text = "Middle Right", .y = TALIGN_CENTER, .x = TALIGN_END },
    { .text = "Bottom Left", .y = TALIGN_END, .x = TALIGN_START },
    { .text = "Bottom Center", .y = TALIGN_END, .x = TALIGN_CENTER },
    { .text = "Bottom Right", .y = TALIGN_END, .x = TALIGN_END }
};
static size_t frames_len = sizeof(frames) / sizeof(AnimationFrame);

static bool key_pressed_cb(TWidget *widget, void *data)
{
    int key = *(int *)data;
    if (key == 'q' || key == 'Q' || key == TKEY_ESC) {
        tui_stop();
    } else if (key == TKEY_SPACE) {
        // Start or stop animation
        if (animation_timer.pending) {
            ml_timer_cancle(&animation_timer);
        } else {
            ml_timer_in(&animation_timer, 0);
        }
    }
    return true;
}

static void animation_cb(MlTimer *self, TLabel *label)
{
    AnimationFrame f = frames[animation_frame];
    // Change label content
    tlabel_set_text(label, f.text);
    label->align_x = f.x;
    label->align_y = f.y;
    tui_update(label);
    // Go to next animation frame
    animation_frame++;
    if (animation_frame >= frames_len) {
        animation_frame = 0;
    }
    // Restart timer
    ml_timer_in(self, animation_interval);
}

int main(int argc, char *argv[])
{
    // Initialise a TUI Application
    tui_init("TUI Example - Animation");
    // Create Label with hello message
    TLabel *label = new(TLabel, hello_msg);
    label->align_x = TALIGN_CENTER;
    label->align_y = TALIGN_CENTER;
    // Set the content of the main layout
    tui_set_content(label);
    // Register a signal handler for pressed keys
    tui_connect_signal("key-pressed", key_pressed_cb);
    // Register handler for the animation
    animation_timer = init(MlTimer, animation_cb, label);
    // Start the TUI application
    tui_start();
    // Cleanup
    destroy(&animation_timer);
    tui_destroy();
    return 0;
}
