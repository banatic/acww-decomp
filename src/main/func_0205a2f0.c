/* func_0205a2f0 @ 0x0205a2f0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char x[0x104];
} Buf;

extern int data_020dd398;
extern int data_020dd3d8;
extern int data_020dd388;

extern void *func_020984e8(void *p);
extern int func_02099020(void *h, int k);
extern void func_02066694(Buf *b);
extern void *func_02099870(void *h);
extern void func_02066024(Buf *b, unsigned char *m, void *a, void *c, void *d, void *e);
extern int func_02097a54(Buf *b);
extern void func_02098ff8(void *h, int k);
extern void func_02066688(Buf *b);

int func_0205a2f0(void *p)
{
    unsigned char m[4];
    Buf buf;
    void *h;

    h = func_020984e8(p);
    if (h == 0) {
        goto zero;
    }
    if (func_02099020(h, 3) == 0) {
        goto zero;
    }
    if (func_02099020(h, 0xe) != 0) {
        goto zero;
    }
    func_02066694(&buf);
    m[0] = 0x1b;
    func_02066024(&buf, m, &data_020dd3d8, &data_020dd388, &data_020dd398, func_02099870(h));
    if (func_02097a54(&buf) != 0) {
        func_02098ff8(h, 0xe);
        func_02066688(&buf);
        return 1;
    }
    func_02066688(&buf);
zero:
    return 0;
}
