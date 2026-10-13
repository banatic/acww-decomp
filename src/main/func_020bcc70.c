/* func_020bcc70 @ 0x020bcc70, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bcdf8(void *obj, int i);
extern void func_020bcda0(void *obj, int i, int a, int b);
extern void func_020bcd7c(void *obj, int *p);

typedef struct {
    char pad_00[0x2f38];
    int timers[4];
} UnkStruct_020bcc70;

void func_020bcc70(UnkStruct_020bcc70 *obj)
{
    int *timers[4];
    int **q;
    int i;
    int *t;

    timers[0] = &obj->timers[0];
    timers[1] = &obj->timers[1];
    timers[2] = &obj->timers[2];
    timers[3] = &obj->timers[3];
    q = timers;
    for (i = 0; i < 4; i++, q++) {
        t = *q;
        *t = *t - 1;
        if (*t > 0) {
            continue;
        }
        if (func_020bcdf8(obj, i) != 0) {
            func_020bcda0(obj, i, 0, 0);
            func_020bcd7c(obj, t);
        }
    }
}
