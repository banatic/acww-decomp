/* func_ov051_02260e2c @ 0x02260e2c, 0x74 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(int);
extern void func_0209e474(void *);
extern int func_020683e4(void *, int, void *, void *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern char data_ov051_02261b68[];

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
} Param;

void func_ov051_02260e2c(Param *p)
{
    unsigned char buf[12];
    unsigned int v;
    int b;
    void *r;

    if (p->unk_1E != 0 && p->unk_1E != 2) {
        return;
    }

    r = func_020682e0(0);
    b = 0x19;

    *(unsigned int *) &buf[4] = 0;
    *(unsigned int *) &buf[8] = 0;
    func_0209e474(&buf[4]);

    if (buf[6] >= 12) {
        b = 0x1a;
    }
    buf[0] = b;

    func_020683e4(r, 0, buf, (void *) data_ov051_02261b68);

    v = buf[6];
    if (v >= 12) {
        v -= 12;
    }
    if (v == 0) {
        v = 12;
    }
    if (v == 12) {
        v = 0;
    }

    func_02015fb0(p, v, 1, 2, 0, 0);
}
