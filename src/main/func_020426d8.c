/* func_020426d8 @ 0x020426d8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209e380(int, void *);
extern void func_0204cc34(void *, void *);

typedef struct {
    unsigned int a;
    unsigned int b;
} UnkStruct_020426d8;

void func_020426d8(int unused, unsigned char *base, int b)
{
    unsigned char *p;
    UnkStruct_020426d8 local;

    local.a = 0;
    local.b = 0;

    p = base + 0x1725c;

    local.a = 0;
    local.b = 0;

    ((unsigned char *) &local)[5] = p[2];
    ((unsigned char *) &local)[4] = p[1];
    ((unsigned char *) &local)[3] = p[0];

    while (func_0209e380(b, &local) < 0) {
        func_0204cc34(base + 0x17254, p);
        ((unsigned char *) &local)[5] = p[2];
        ((unsigned char *) &local)[4] = p[1];
        ((unsigned char *) &local)[3] = p[0];
    }
}
