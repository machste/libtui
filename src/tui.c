#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <signal.h>
#include <masc.h>
#include <tui.h>
#include <tui/mainlayout.h>


// Input via stdin and signal handling of SIGWINCH
static Io input;
static struct sigaction winch_act, ncurses_winch_act;
static MlEvent *resize_event = NULL;
// Content
static Str app_name;
static TMainLayout *main_layout = NULL;
// List of signal callbacks
List *signal_cbs;


static void sigwinch_handler(int sig)
{
    // Fire resize event
    ml_event_fire(resize_event);
    // Call the original signal handler of ncurses manually
    if (ncurses_winch_act.sa_handler != SIG_DFL
            && ncurses_winch_act.sa_handler != SIG_IGN) {
        ncurses_winch_act.sa_handler(sig);
    }
}

static void redraw_main_layout(void)
{
    if (main_layout == NULL) {
        return;
    }
    TRect r = (TRect){ .y = 0, .x = 0};
    getmaxyx(stdscr, r.h, r.w);
    set_geometry(main_layout, r);
    tui_update(main_layout);
}

static void resize_event_cb(MlEvent *event, void *arg)
{
    int key = getch();
    if (key == KEY_RESIZE) {
        redraw_main_layout();
    } else {
        log_warn("resize_event_cb: Expected KEY_RESIZE, instead got %d!", key);
        ungetch(key);
    }
}

static void keyboard_input_cb(MlIo *self, int fd, ml_io_flag_t events, void *arg)
{
    if (events & ML_IO_READ) {
        while (true) {
            int key = getch();
            if (key == ERR)
                break;
            if (key == KEY_RESIZE) {
                log_warn("keyboard_intput_cb: KEY_RESIZE not expected!");
                redraw_main_layout();
            } else {
                twidget_emit_singal(main_layout, "key-pressed", &key);
            }
        }
    }
}

void tui_init(const char *name)
{
    str_init_cstr(&app_name, name);
    // Initialise ncurses
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    set_escdelay(50);
    // Add handling of SIGWINCH after setting up ncurses
    winch_act.sa_handler = sigwinch_handler;
    sigaction(SIGWINCH, &winch_act, &ncurses_winch_act);
    // Register stdin to main loop
    mloop_init();
    input = init(Io, STDIN_FILENO);
    mloop_io_new(&input, ML_IO_READ, keyboard_input_cb, NULL);
    resize_event = mloop_event_new(resize_event_cb, NULL);
    // Initialise main layout
    main_layout = tmainlayout_new(app_name.cstr);
}

void tui_destroy(void)
{
    delete(main_layout);
    destroy(&input);
    destroy(&app_name);
}

void tui_set_content(TWidget *widget)
{
    tmainlayout_set_center(main_layout, widget);
}

void tui_start(void)
{
    // Perform a "sacrificial" refresh on the not used stanard screen
    refresh();
    // Draw the main layout
    redraw_main_layout();
    // Run the main loop
    mloop_run();
    // Clean up after the main loop is done
    endwin();
}

void tui_stop(void)
{
    mloop_stop();
}

void tui_update(TWidget *widget)
{
    draw(widget);
    doupdate();
}


void tui_connect_signal(const char *name, tsignal_cb cb)
{
    twidget_connect_signal(main_layout, name, cb);
}
