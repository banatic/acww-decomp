/* Playing the game: a window that shows both screens as the run draws them, the keyboard and
 * the mouse as the DS's buttons and touch screen, the run paced to the DS's frame rate, and
 * the save chip written back to a save file. Built by tools/play.py with run.c (RUN_FRONT_END)
 * and the rest of the runtime; docs/play.md describes it from the player's side.
 *
 *     acww-play [options] [SAVE]
 *
 * The run itself is the headless one (run.c, configured by the environment as tools/run.py
 * configures it); this file only sets the environment, then watches the run through three
 * hooks that are NULL in the headless program: run_frame_hook (run.h) on the emulation's
 * thread once per frame, where the pacer waits and the input for the frame is handed over
 * (input_live), frame_output_hook (frame.h) on the drawing thread with each finished frame,
 * and arm7_backup (arm7.h), the save chip's image and its write count.
 *
 * Windows only for now (Win32: a window of its own thread, StretchDIBits, a high-resolution
 * waitable timer). There is no sound: the ARM7 is simulated at its protocol (arm7.c), which
 * acknowledges the sound driver's command lists without running the ARM7's sound code.
 */
#ifndef _WIN32
#error "the play front end is written for Windows (Win32)"
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm7.h"
#include "frame.h"
#include "input.h"
#include "run.h"

/* The DS's frame: 263 lines of 2130 bus cycles at 33,513,982 Hz, about 59.8261 a second. */
#define DS_CYCLES_PER_FRAME (263.0 * 2130.0)
#define DS_BUS_HZ 33513982.0

#define SCREEN_W 256
#define SCREEN_H 192

/* the buttons in the recording's bits (input.h) */
enum {
    KEY_A = 1u << 0,
    KEY_B = 1u << 1,
    KEY_SELECT = 1u << 2,
    KEY_START = 1u << 3,
    KEY_RIGHT = 1u << 4,
    KEY_LEFT = 1u << 5,
    KEY_UP = 1u << 6,
    KEY_DOWN = 1u << 7,
    KEY_R = 1u << 8,
    KEY_L = 1u << 9,
    KEY_X = 1u << 10,
    KEY_Y = 1u << 11,
};

/* Options -------------------------------------------------------------------------------- */

static struct {
    char rom[MAX_PATH], modules[MAX_PATH], symbols[MAX_PATH], policy[MAX_PATH], form[32];
    char save[MAX_PATH];
    const char *rtc, *input;
    int reference, read_only, scale, background, unpaced;
    uint32_t stop_frame; /* 0: none */
} opt;

static void usage(void)
{
    fprintf(stderr, "usage: acww-play [options] [SAVE]\n"
                    "  SAVE            the save file (256 KB flash image), read at start and written when the game\n"
                    "                  saves; created by the first save if it does not exist (a new game).\n"
                    "                  Default: %%APPDATA%%\\acwwdecomp\\acww.sav\n"
                    "  --read-only     never write the save file\n"
                    "  --reference     run every function as the ROM's code (the interpreter)\n"
                    "  --rtc TIME      start the clock at \"YYYY-MM-DD HH:MM:SS\" (default: the PC's clock)\n"
                    "  --input FILE    also play an input recording (runtime/input.h), under the live input\n"
                    "  --scale N       the window's starting size: N times the DS's screens (default 2)\n"
                    "  --frames N      save and quit after N frames (for scripted checks)\n"
                    "  --fast          no pacing: as fast as the PC runs it (as with Tab held)\n"
                    "  --config FILE   the build's paths (default: the .cfg beside the program, from tools/play.py)\n"
                    "  ACWW_BACKGROUND=1 in the environment opens the window without taking the focus\n");
    exit(2);
}

/* "key=value" lines; the paths tools/play.py wrote for this program. */
static int read_config(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }
    char line[2 * MAX_PATH];
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\r\n")] = 0;
        char *eq = strchr(line, '=');
        if (eq == NULL || line[0] == '#') {
            continue;
        }
        *eq = 0;
        const char *value = eq + 1;
        char *to = strcmp(line, "rom") == 0       ? opt.rom
                   : strcmp(line, "modules") == 0 ? opt.modules
                   : strcmp(line, "symbols") == 0 ? opt.symbols
                   : strcmp(line, "policy") == 0  ? opt.policy
                   : strcmp(line, "form") == 0    ? opt.form
                                                  : NULL;
        if (to != NULL) {
            snprintf(to, to == opt.form ? sizeof(opt.form) : MAX_PATH, "%s", value);
        }
    }
    fclose(f);
    return 0;
}

static int file_exists(const char *path)
{
    DWORD a = GetFileAttributesA(path);
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static void default_save(char *out)
{
    char base[MAX_PATH];
    DWORD n = GetEnvironmentVariableA("APPDATA", base, sizeof(base));
    if (n == 0 || n >= sizeof(base)) {
        snprintf(out, MAX_PATH, "acww.sav");
        return;
    }
    char dir[MAX_PATH];
    snprintf(dir, sizeof(dir), "%s\\acwwdecomp", base);
    CreateDirectoryA(dir, NULL);
    snprintf(out, MAX_PATH, "%s\\acww.sav", dir);
}

/* Shared state ------------------------------------------------------------------------------ */

/* Written by the window's thread, read by the emulation's at each frame. */
static volatile LONG keys_held;  /* buttons down now */
static volatile LONG keys_taps;  /* buttons pressed since the last frame (a press shorter than a frame still counts) */
static volatile LONG pen_state;  /* bit 31: down; bits 0-7 x, 8-15 y */
static volatile LONG pen_tap;    /* the same for a touch that began since the last frame (bit 31 set) */
static volatile LONG fast;       /* Tab held: no pacing */
static volatile LONG quit_asked; /* the window was closed */

static HWND window;
static HANDLE window_ready;

/* The last frame drawn, upper screen above the lower one, as the drawing thread left it. */
static uint32_t shown[SCREEN_W * SCREEN_H * 2];
static SRWLOCK shown_lock = SRWLOCK_INIT;
static volatile LONG repaint_posted;
static char title[256] = "Animal Crossing: Wild World";
static SRWLOCK title_lock = SRWLOCK_INIT;

#define WM_PLAY_FRAME (WM_APP + 1)
#define WM_PLAY_TITLE (WM_APP + 2)

/* The save file ----------------------------------------------------------------------------- */

static uint64_t save_writes_seen, save_writes_flushed;
static uint32_t save_quiet_frames;
static int save_backed_up;
static uint32_t frame_now;

/* Writes the chip's image to the save file: to a temporary file first, then in its place, so
 * a crash never leaves half a save. The first time an existing file is replaced it is kept as
 * SAVE.bak (unless there is one). */
static void save_flush(const char *why)
{
    uint64_t writes;
    const uint8_t *image = arm7_backup(&writes);
    if (opt.read_only || image == NULL || writes == save_writes_flushed) {
        return;
    }
    if (!save_backed_up) {
        char bak[MAX_PATH + 8];
        snprintf(bak, sizeof(bak), "%s.bak", opt.save);
        if (file_exists(opt.save) && !file_exists(bak)) {
            CopyFileA(opt.save, bak, TRUE);
        }
        save_backed_up = 1;
    }
    char tmp[MAX_PATH + 8];
    snprintf(tmp, sizeof(tmp), "%s.tmp", opt.save);
    FILE *f = fopen(tmp, "wb");
    if (f == NULL || fwrite(image, 1, ARM7_BACKUP_SIZE, f) != ARM7_BACKUP_SIZE || fclose(f) != 0) {
        fprintf(stderr, "play: cannot write %s\n", tmp);
        return;
    }
    if (!MoveFileExA(tmp, opt.save, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        fprintf(stderr, "play: cannot replace %s (error %lu)\n", opt.save, GetLastError());
        return;
    }
    save_writes_flushed = writes;
    printf("play: frame %u: saved %s (%s, %llu writes to the chip)\n", frame_now, opt.save, why, (unsigned long long) writes);
    fflush(stdout);
}

static void at_exit(void)
{
    save_flush("at exit");
}

/* The window -------------------------------------------------------------------------------- */

typedef struct Layout {
    int scale, x, y; /* the screens' size factor and top-left corner in the client area */
} Layout;

static Layout layout_of(HWND hwnd)
{
    RECT r;
    GetClientRect(hwnd, &r);
    int w = r.right - r.left, h = r.bottom - r.top;
    int s = w / SCREEN_W < h / (2 * SCREEN_H) ? w / SCREEN_W : h / (2 * SCREEN_H);
    if (s < 1) {
        s = 1;
    }
    Layout l = {s, (w - SCREEN_W * s) / 2, (h - 2 * SCREEN_H * s) / 2};
    return l;
}

static void paint(HWND hwnd, HDC dc)
{
    Layout l = layout_of(hwnd);
    RECT r;
    GetClientRect(hwnd, &r);
    /* the borders around the screens, black */
    HBRUSH black = (HBRUSH) GetStockObject(BLACK_BRUSH);
    RECT parts[4] = {
        {0, 0, r.right, l.y},
        {0, l.y + 2 * SCREEN_H * l.scale, r.right, r.bottom},
        {0, l.y, l.x, l.y + 2 * SCREEN_H * l.scale},
        {l.x + SCREEN_W * l.scale, l.y, r.right, l.y + 2 * SCREEN_H * l.scale},
    };
    for (int i = 0; i < 4; i++) {
        if (parts[i].right > parts[i].left && parts[i].bottom > parts[i].top) {
            FillRect(dc, &parts[i], black);
        }
    }
    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = SCREEN_W;
    bi.bmiHeader.biHeight = -2 * SCREEN_H; /* top-down */
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32; /* 0x00RRGGBB, as frame_output's pixels are */
    bi.bmiHeader.biCompression = BI_RGB;
    SetStretchBltMode(dc, COLORONCOLOR);
    AcquireSRWLockShared(&shown_lock);
    StretchDIBits(dc, l.x, l.y, SCREEN_W * l.scale, 2 * SCREEN_H * l.scale, 0, 0, SCREEN_W, 2 * SCREEN_H, shown, &bi,
                  DIB_RGB_COLORS, SRCCOPY);
    ReleaseSRWLockShared(&shown_lock);
}

static uint32_t key_of(WPARAM vk)
{
    switch (vk) {
        case VK_UP:
            return KEY_UP;
        case VK_DOWN:
            return KEY_DOWN;
        case VK_LEFT:
            return KEY_LEFT;
        case VK_RIGHT:
            return KEY_RIGHT;
        case 'X':
            return KEY_A;
        case 'Z':
            return KEY_B;
        case 'S':
            return KEY_X;
        case 'A':
            return KEY_Y;
        case 'Q':
            return KEY_L;
        case 'W':
            return KEY_R;
        case VK_RETURN:
            return KEY_START;
        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
        case VK_BACK:
            return KEY_SELECT;
        default:
            return 0;
    }
}

/* The pen at a client position, on the lower screen (clamped there while dragging). */
static LONG pen_at(HWND hwnd, int mx, int my, int clamp, int *inside)
{
    Layout l = layout_of(hwnd);
    int x = (mx - l.x) / l.scale, y = (my - l.y - SCREEN_H * l.scale) / l.scale;
    if (mx < l.x || my < l.y + SCREEN_H * l.scale) {
        x = mx < l.x ? -1 : x;
        y = my < l.y + SCREEN_H * l.scale ? -1 : y;
    }
    *inside = x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H;
    if (!*inside && !clamp) {
        return 0;
    }
    x = x < 0 ? 0 : x >= SCREEN_W ? SCREEN_W - 1 : x;
    y = y < 0 ? 0 : y >= SCREEN_H ? SCREEN_H - 1 : y;
    return (LONG) (0x80000000u | (uint32_t) y << 8 | (uint32_t) x);
}

static void screenshot(void)
{
    static uint32_t copy[SCREEN_W * SCREEN_H * 2];
    AcquireSRWLockShared(&shown_lock);
    memcpy(copy, shown, sizeof(copy));
    ReleaseSRWLockShared(&shown_lock);
    char dir[MAX_PATH], path[MAX_PATH + 64];
    snprintf(dir, sizeof(dir), "%s", opt.save);
    char *slash = strrchr(dir, '\\'), *other = strrchr(dir, '/');
    slash = other > slash ? other : slash;
    if (slash != NULL) {
        slash[1] = 0;
    } else {
        dir[0] = 0;
    }
    SYSTEMTIME t;
    GetLocalTime(&t);
    snprintf(path, sizeof(path), "%sacww-%04u%02u%02u-%02u%02u%02u.png", dir, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute,
             t.wSecond);
    if (png_write(path, copy, SCREEN_W, 2 * SCREEN_H) == 0) {
        printf("play: screenshot %s\n", path);
    } else {
        printf("play: cannot write %s\n", path);
    }
    fflush(stdout);
}

static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static int pen_captured;
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(hwnd, &ps);
            paint(hwnd, dc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_PRINTCLIENT:
            paint(hwnd, (HDC) wp);
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_SIZE:
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        case WM_PLAY_FRAME:
            InterlockedExchange(&repaint_posted, 0);
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        case WM_PLAY_TITLE: {
            char t[256];
            AcquireSRWLockShared(&title_lock);
            memcpy(t, title, sizeof(t));
            ReleaseSRWLockShared(&title_lock);
            SetWindowTextA(hwnd, t);
            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: {
            if (wp == VK_TAB) {
                InterlockedExchange(&fast, 1);
                return 0;
            }
            if (wp == VK_F12) {
                if (!(lp & (1 << 30))) {
                    screenshot();
                }
                return 0;
            }
            uint32_t k = key_of(wp);
            if (k != 0) {
                InterlockedOr(&keys_held, (LONG) k);
                InterlockedOr(&keys_taps, (LONG) k);
                return 0;
            }
            break;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            if (wp == VK_TAB) {
                InterlockedExchange(&fast, 0);
                return 0;
            }
            uint32_t k = key_of(wp);
            if (k != 0) {
                InterlockedAnd(&keys_held, (LONG) ~k);
                return 0;
            }
            break;
        }
        case WM_KILLFOCUS:
            InterlockedExchange(&keys_held, 0);
            InterlockedExchange(&fast, 0);
            return 0;
        case WM_LBUTTONDOWN: {
            int inside;
            LONG p = pen_at(hwnd, (short) LOWORD(lp), (short) HIWORD(lp), 0, &inside);
            if (inside) {
                SetCapture(hwnd);
                pen_captured = 1;
                InterlockedExchange(&pen_state, p);
                InterlockedExchange(&pen_tap, p);
            }
            return 0;
        }
        case WM_MOUSEMOVE:
            if (pen_captured) {
                int inside;
                InterlockedExchange(&pen_state, pen_at(hwnd, (short) LOWORD(lp), (short) HIWORD(lp), 1, &inside));
            }
            return 0;
        case WM_LBUTTONUP:
        case WM_CAPTURECHANGED:
            if (pen_captured) {
                pen_captured = 0;
                InterlockedExchange(&pen_state, 0);
                if (msg == WM_LBUTTONUP) {
                    ReleaseCapture();
                }
            }
            return 0;
        case WM_CLOSE:
            /* the run saves and ends at its next frame; if it does not, the program ends anyway */
            InterlockedExchange(&quit_asked, 1);
            SetTimer(hwnd, 1, 5000, NULL);
            return 0;
        case WM_TIMER:
            if (wp == 1) {
                fprintf(stderr, "play: the run did not end; quitting\n");
                save_flush("quit");
                ExitProcess(1);
            }
            return 0;
        default:
            break;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

static DWORD WINAPI window_thread(LPVOID unused)
{
    (void) unused;
    HINSTANCE inst = GetModuleHandleA(NULL);
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = window_proc;
    wc.hInstance = inst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpszClassName = "AcwwPlay";
    RegisterClassA(&wc);
    RECT r = {0, 0, SCREEN_W * opt.scale, 2 * SCREEN_H * opt.scale};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
    window = CreateWindowExA(0, "AcwwPlay", title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left,
                             r.bottom - r.top, NULL, NULL, inst, NULL);
    SetEvent(window_ready);
    if (window == NULL) {
        fprintf(stderr, "play: cannot open the window\n");
        return 1;
    }
    ShowWindow(window, opt.background ? SW_SHOWNOACTIVATE : SW_SHOWNORMAL);
    MSG m;
    while (GetMessageA(&m, NULL, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageA(&m);
    }
    return 0;
}

/* The drawing thread's frames ---------------------------------------------------------------- */

static void on_frame_output(uint32_t frame, const uint32_t *upper, const uint32_t *lower)
{
    (void) frame;
    AcquireSRWLockExclusive(&shown_lock);
    memcpy(shown, upper, sizeof(uint32_t) * SCREEN_W * SCREEN_H);
    memcpy(shown + SCREEN_W * SCREEN_H, lower, sizeof(uint32_t) * SCREEN_W * SCREEN_H);
    ReleaseSRWLockExclusive(&shown_lock);
    if (window != NULL && InterlockedExchange(&repaint_posted, 1) == 0) {
        PostMessageA(window, WM_PLAY_FRAME, 0, 0);
    }
}

/* The pacer --------------------------------------------------------------------------------- */

static LARGE_INTEGER qpc_freq;
static HANDLE pace_timer;
static double ticks_per_frame, next_tick;
static int64_t busy_ticks, stats_start, stats_frames_start_tick;
static uint32_t stats_frames;

static int64_t now_ticks(void)
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return t.QuadPart;
}

/* Waits until the frame's moment: the high-resolution timer for all but the last
 * millisecond, then a spin, so Sleep's granularity loses no time. */
static void wait_until(double tick)
{
    int64_t now = now_ticks();
    double left = tick - (double) now;
    double margin = (double) qpc_freq.QuadPart / 1000.0; /* 1 ms */
    if (left > margin * 1.5 && pace_timer != NULL) {
        LARGE_INTEGER due;
        due.QuadPart = -(LONGLONG) ((left - margin) * 1e7 / (double) qpc_freq.QuadPart); /* 100 ns units */
        if (SetWaitableTimer(pace_timer, &due, 0, NULL, NULL, FALSE)) {
            WaitForSingleObject(pace_timer, INFINITE);
        }
    } else if (left > margin * 1.5) {
        Sleep((DWORD) ((left - margin) * 1000.0 / (double) qpc_freq.QuadPart));
    }
    while ((double) now_ticks() < tick) {
        YieldProcessor();
    }
}

static void set_title(const char *text)
{
    AcquireSRWLockExclusive(&title_lock);
    snprintf(title, sizeof(title), "%s", text);
    ReleaseSRWLockExclusive(&title_lock);
    if (window != NULL) {
        PostMessageA(window, WM_PLAY_TITLE, 0, 0);
    }
}

static void pace(void)
{
    int64_t start = now_ticks();
    if (next_tick == 0) {
        next_tick = (double) start;
        stats_start = stats_frames_start_tick = start;
    }
    next_tick += ticks_per_frame;
    if (fast || opt.unpaced || (double) start > next_tick + 4 * ticks_per_frame) {
        next_tick = (double) start; /* fast forward, or too far behind: no catching up */
    } else {
        wait_until(next_tick);
    }
    int64_t end = now_ticks();
    busy_ticks += start - stats_frames_start_tick;
    stats_frames_start_tick = end;
    stats_frames++;
    double seconds = (double) (end - stats_start) / (double) qpc_freq.QuadPart;
    if (seconds >= 5.0) {
        double fps = stats_frames / seconds;
        double busy = (double) busy_ticks / (double) (end - stats_start);
        printf("play: frame %u, %.2f fps (the DS: %.2f), emulation busy %.0f%% of the time%s\n", frame_now, fps,
               DS_BUS_HZ / DS_CYCLES_PER_FRAME, busy * 100.0, fast || opt.unpaced ? ", fast forward" : "");
        fflush(stdout);
        char t[256];
        snprintf(t, sizeof(t), "Animal Crossing: Wild World - %s - %.1f fps", opt.form, fps);
        set_title(t);
        stats_start = end;
        stats_frames = 0;
        busy_ticks = 0;
    }
}

/* Once per frame, on the emulation's thread ------------------------------------------------ */

static uint32_t taps_last;
static LONG pen_tap_last;
static uint32_t quit_wait;

static void on_frame(uint32_t frame)
{
    frame_now = frame;
    if (window_ready == NULL) {
        /* the window's thread starts here, after native_reserve has kept the DS's address
           ranges from the host's allocations (native_run.h) */
        window_ready = CreateEventA(NULL, TRUE, FALSE, NULL);
        HANDLE t = CreateThread(NULL, 0, window_thread, NULL, 0, NULL);
        if (t == NULL) {
            fprintf(stderr, "play: cannot start the window's thread\n");
            exit(1);
        }
        CloseHandle(t);
        WaitForSingleObject(window_ready, INFINITE);
    }

    /* the input for this frame: what is held, and presses (and touches) that began and ended
       since the last frame, held for two frames so the game's reader sees them */
    uint32_t taps = (uint32_t) InterlockedExchange(&keys_taps, 0);
    uint32_t keys = (uint32_t) keys_held | taps | taps_last;
    taps_last = taps;
    LONG pen = pen_state;
    LONG tap = InterlockedExchange(&pen_tap, 0);
    if (!(pen & 0x80000000) && (tap | pen_tap_last) & 0x80000000) {
        pen = tap & 0x80000000 ? tap : pen_tap_last;
    }
    pen_tap_last = tap;
    input_live(keys, (pen & 0x80000000) != 0, pen & 0xff, (pen >> 8) & 0xff);

    /* the save: written once the game has not written to the chip for half a second */
    uint64_t writes;
    arm7_backup(&writes);
    if (writes != save_writes_seen) {
        save_writes_seen = writes;
        save_quiet_frames = 0;
    } else if (writes != save_writes_flushed && ++save_quiet_frames >= 30) {
        save_flush("the game saved");
    }

    /* quitting: after the game's writes to the chip have settled (at most 3 seconds more) */
    if (quit_asked || (opt.stop_frame && frame >= opt.stop_frame)) {
        if (writes == save_writes_flushed || save_quiet_frames >= 30 || ++quit_wait > 180) {
            save_flush(quit_asked ? "quit" : "frame limit");
            printf("play: ended at frame %u\n", frame);
            fflush(stdout);
            exit(0);
        }
    }
    pace();
}

/* main -------------------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    opt.scale = 2;
    char config[MAX_PATH + 8] = "";
    const char *save = NULL;
    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        int more = i + 1 < argc;
        if (strcmp(a, "--read-only") == 0) {
            opt.read_only = 1;
        } else if (strcmp(a, "--reference") == 0) {
            opt.reference = 1;
        } else if (strcmp(a, "--fast") == 0) {
            opt.unpaced = 1;
        } else if (strcmp(a, "--rtc") == 0 && more) {
            opt.rtc = argv[++i];
        } else if (strcmp(a, "--input") == 0 && more) {
            opt.input = argv[++i];
        } else if (strcmp(a, "--scale") == 0 && more) {
            opt.scale = atoi(argv[++i]);
        } else if (strcmp(a, "--frames") == 0 && more) {
            opt.stop_frame = (uint32_t) strtoul(argv[++i], NULL, 10);
        } else if (strcmp(a, "--config") == 0 && more) {
            snprintf(config, sizeof(config), "%s", argv[++i]);
        } else if (a[0] == '-' || save != NULL) {
            usage();
        } else {
            save = a;
        }
    }
    if (opt.scale < 1 || opt.scale > 8) {
        opt.scale = 2;
    }
    if (config[0] == 0) {
        /* beside the program: acww-play.exe -> acww-play.cfg */
        GetModuleFileNameA(NULL, config, MAX_PATH);
        char *dot = strrchr(config, '.');
        if (dot != NULL) {
            strcpy(dot, ".cfg");
        }
    }
    if (read_config(config) != 0 || opt.rom[0] == 0 || opt.modules[0] == 0 || opt.symbols[0] == 0) {
        fprintf(stderr, "play: cannot read the build's paths from %s; build with `python tools/play.py`\n", config);
        return 2;
    }
    if (save != NULL) {
        snprintf(opt.save, sizeof(opt.save), "%s", save);
    } else {
        default_save(opt.save);
    }
    if (opt.reference || opt.policy[0] == 0) {
        snprintf(opt.form, sizeof(opt.form), "Reference");
    }
    char *e = getenv("ACWW_BACKGROUND");
    opt.background = e != NULL && atoi(e) != 0;

    /* the run's environment, as tools/run.py sets it */
    _putenv_s("RUN_NATIVE", opt.reference || opt.policy[0] == 0 ? "0" : "1");
    _putenv_s("RUN_NATIVE_POLICY", opt.reference ? "" : opt.policy);
    _putenv_s("RUN_SAVE", file_exists(opt.save) ? opt.save : "");
    _putenv_s("RUN_RTC", opt.rtc ? opt.rtc : "");
    _putenv_s("RUN_INPUT", opt.input ? opt.input : "");
    const char *cleared[] = {"RUN_HASH",          "RUN_PNG",      "RUN_DUMP3D",   "RUN_NATIVE_RECORD",
                             "RUN_NATIVE_REPLAY", "RUN_RAM_HASH", "RUN_RAM_DUMP", "RUN_NATIVE_LEARN",
                             "RUN_CLEAN_RAN",     "RUN_TRACE",    "RUN_CALLS"};
    for (size_t i = 0; i < sizeof(cleared) / sizeof(cleared[0]); i++) {
        _putenv_s(cleared[i], "");
    }

    printf("play: %s, save %s%s%s\n", opt.form, opt.save, file_exists(opt.save) ? "" : " (none yet: a new game)",
           opt.read_only ? ", read only" : "");
    printf("play: keys: arrows = +Control Pad, X = A, Z = B, S = X, A = Y, Q = L, W = R, Enter = START,\n"
           "      Shift or Backspace = SELECT, mouse on the lower screen = touch, Tab = fast forward, F12 = screenshot\n");
    fflush(stdout);

    QueryPerformanceFrequency(&qpc_freq);
    ticks_per_frame = (double) qpc_freq.QuadPart * DS_CYCLES_PER_FRAME / DS_BUS_HZ;
    pace_timer = CreateWaitableTimerExW(NULL, NULL, 0x00000002 /* CREATE_WAITABLE_TIMER_HIGH_RESOLUTION */, TIMER_ALL_ACCESS);
    if (pace_timer == NULL) {
        pace_timer = CreateWaitableTimerW(NULL, TRUE, NULL);
    }
    run_frame_hook = on_frame;
    frame_output_hook = on_frame_output;
    atexit(at_exit);

    char *run_argv[] = {argv[0], opt.rom, opt.modules, opt.symbols, "0", NULL};
    return run_main(5, run_argv);
}
