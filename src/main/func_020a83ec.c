/* func_020a83ec @ 0x020a83ec, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ab8dc(void *);
extern int func_020a8a34(void *, int);
extern void *func_020ab8c4(void *);

struct Something {
    char pad_00[4];
    unsigned int mode;
    int a;
    int b;
};

unsigned int func_020a83ec(struct Something *p)
{
    unsigned int mode, count, i, sum;
    int next, delta;
    char buf[0x5c];

    mode = p->mode;
    count = 0;
    if (mode == 0 || mode == 4) {
        count = 2;
    } else if (mode == 1 || mode == 5) {
        count = 3;
    } else if (mode == 2 || mode == 6) {
        count = 4;
    } else if (mode == 3 || mode == 7) {
        count = 5;
    }

    func_020ab8dc(buf);
    sum = 2;
    next = p->b + p->a + 2;

    for (i = 0; i < count; i++) {
        func_020a8a34(buf, next);
        delta = *((int *) (buf + 4)) + 2;
        sum += delta;
        next += delta;
    }

    func_020ab8c4(buf);
    return sum;
}
