/* func_020466e0 @ 0x020466e0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *ptr);

typedef struct Pair {
    int x;
    int y;
} Pair;

extern Pair *func_020466d8(void);

int func_020466e0(int a, int b)
{
    int idx = -1;
    if (func_02073d90(data_020ccf94) == 0) {
        Pair *p = func_020466d8();
        int i = 0;
        while (i < 24) {
            if (p->x == a && p->y == b) {
                idx = i;
                break;
            }
            p++;
            i++;
        }
    } else {
        idx = (a + b) % 24;
    }
    return idx;
}
