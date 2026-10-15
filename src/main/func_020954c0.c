/* func_020954c0 @ 0x020954c0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec3 {
    int x;
    int y;
    int z;
};
struct Big {
    char pad_00[0x450];
    int a;
    int b;
    int c;
};

extern struct Big *func_02096718(void *arg);
extern int func_0203f7d0(void *a, void *b);

int func_020954c0(struct Vec3 *out, void *arg)
{
    struct Big *p = func_02096718(arg);

    if (p != 0) {
        if (p->a == 0 && p->b == 0 && p->c == 0) {
            return 0;
        }

        out->x = p->a;
        out->y = p->b;
        out->z = p->c;

        func_0203f7d0(out, out);
        return 1;
    }

    return 0;
}
