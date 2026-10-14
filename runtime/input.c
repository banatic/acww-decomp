/* The input recording; see input.h. */
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

typedef struct InputEvent {
    uint32_t frame;
    uint32_t keys; /* bits 0-9 as KEYINPUT, bits 10-11 X and Y */
    int touch, x, y;
} InputEvent;

static InputEvent *events;
static int event_count, event_capacity, next_event;
static InputEvent state;

static const struct {
    const char *name;
    uint32_t bit;
} key_names[] = {
    {"A", 1u << 0},  {"B", 1u << 1},    {"SELECT", 1u << 2}, {"START", 1u << 3}, {"RIGHT", 1u << 4}, {"LEFT", 1u << 5},
    {"UP", 1u << 6}, {"DOWN", 1u << 7}, {"R", 1u << 8},      {"L", 1u << 9},     {"X", 1u << 10},    {"Y", 1u << 11},
};

static int parse_keys(const char *text, uint32_t *keys)
{
    *keys = 0;
    if (strcmp(text, "-") == 0) {
        return 0;
    }
    char copy[256];
    snprintf(copy, sizeof(copy), "%s", text);
    for (char *tok = strtok(copy, "+"); tok != NULL; tok = strtok(NULL, "+")) {
        int found = 0;
        for (size_t i = 0; i < sizeof(key_names) / sizeof(key_names[0]); i++) {
            if (strcmp(tok, key_names[i].name) == 0) {
                *keys |= key_names[i].bit;
                found = 1;
            }
        }
        if (!found) {
            return -1;
        }
    }
    return 0;
}

int input_load(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }
    char line[512], keys[256], touch[64];
    unsigned frame;
    int line_no = 0;
    while (fgets(line, sizeof(line), f) != NULL) {
        line_no++;
        char *p = line;
        while (*p == ' ' || *p == '\t') {
            p++;
        }
        if (*p == '#' || *p == '\n' || *p == '\r' || *p == '\0') {
            continue;
        }
        if (sscanf(p, "%u %255s %63s", &frame, keys, touch) != 3) {
            fprintf(stderr, "input: %s:%d: expected '<frame> <keys> <touch>'\n", path, line_no);
            fclose(f);
            return -1;
        }
        InputEvent e;
        memset(&e, 0, sizeof(e));
        e.frame = frame;
        if (parse_keys(keys, &e.keys) != 0) {
            fprintf(stderr, "input: %s:%d: unknown key in '%s'\n", path, line_no, keys);
            fclose(f);
            return -1;
        }
        if (strcmp(touch, "-") != 0) {
            if (sscanf(touch, "%d,%d", &e.x, &e.y) != 2 || e.x < 0 || e.x > 255 || e.y < 0 || e.y > 191) {
                fprintf(stderr, "input: %s:%d: touch is 'x,y' on the 256x192 screen or '-'\n", path, line_no);
                fclose(f);
                return -1;
            }
            e.touch = 1;
        }
        if (event_count > 0 && e.frame < events[event_count - 1].frame) {
            fprintf(stderr, "input: %s:%d: frames must not decrease\n", path, line_no);
            fclose(f);
            return -1;
        }
        if (event_count == event_capacity) {
            event_capacity = event_capacity ? event_capacity * 2 : 64;
            events = realloc(events, (size_t) event_capacity * sizeof(InputEvent));
        }
        events[event_count++] = e;
    }
    fclose(f);
    next_event = 0;
    input_frame(0);
    return 0;
}

void input_frame(uint32_t frame)
{
    while (next_event < event_count && events[next_event].frame <= frame) {
        state = events[next_event++];
    }
}

uint32_t input_keys(void)
{
    input_frame(io_frame());
    return state.keys & 0x3ffu;
}

uint32_t input_keys_xy(void)
{
    input_frame(io_frame());
    return (state.keys >> 10) & 3u;
}

int input_touch(int *x, int *y)
{
    input_frame(io_frame());
    *x = state.x;
    *y = state.y;
    return state.touch;
}
