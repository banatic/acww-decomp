/* func_020afa14 @ 0x020afa14, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int x;
    int y;
} Pair;

extern int func_020afc84(Pair *p);
extern unsigned int func_0209e3ac(Pair *p, void *q, int n);

int func_020afa14(void *p0, void *p1)
{
    Pair local;
    local.x = 0;
    local.y = 0;
    if (func_020afc84(&local) && func_0209e3ac(&local, p1, 0x3c) + 1 <= 1) {
        return 1;
    }
    return 0;
}
