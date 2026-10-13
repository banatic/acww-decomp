/* func_020872d0 @ 0x020872d0, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc7a8[];

extern void func_0209dfd8(void *dst, const void *src, int c, int d, int e);
extern void func_0209e474(void *);
extern void func_0209e140(void *p, int n);
extern int func_0209e3ac(void *a, void *b, int n);
extern int func_0209e380(void *a, void *b);
extern void func_0209f100(void *p, int n);
extern void func_02087274(void *obj, void *p);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

void func_020872d0(void *obj)
{
    Pair a;
    Pair b;

    func_0209dfd8(&a, (char *) obj + 4, 6, 0, 0);
    b.unk_00 = 0;
    b.w1 = 0;
    func_0209e474(&b);
    if (((unsigned char *) &b)[5] != 0 || ((unsigned char *) &b)[4] != 1 || ((unsigned char *) &b)[3] != 1) {
        if (((unsigned char *) &b)[2] < 6) {
            func_0209e140(&b, 1);
            ((unsigned char *) &b)[2] = 6;
            ((unsigned char *) &b)[1] = 0;
            ((unsigned char *) &b)[0] = 0;
        }
    }
    if (func_0209e3ac(&b, &a, 0x38) == 1) {
        if (func_0209e380(&a, &b) >= 7) {
            func_0209f100(data_021dc7a8, 4);
            func_02087274(obj, &b);
        }
    }
}
