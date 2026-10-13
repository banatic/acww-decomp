/* func_020863dc @ 0x020863dc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Arg {
    int x;
    int y;
};
struct Pair {
    int x;
    int y;
};
extern struct Pair data_021d27e0[8];
extern void func_02034240(void *out, int a, int b, int c, int d);
extern void func_0203423c(void *buf);

int func_020863dc(struct Arg *arg)
{
    struct Pair *p;
    int i;
    char buf[64];

    p = data_021d27e0;
    i = 0;
    while (i < 8) {
        func_02034240(buf, arg->x + p->x, arg->y + p->y, 0, 0);
        if (*(int *) (buf + 52) == 4) {
            func_0203423c(buf);
            return 1;
        }
        p++;
        func_0203423c(buf);
        i++;
    }
    return 0;
}
