/* func_02079db8 @ 0x02079db8, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char b[0x2c];
} UnkStruct_02079db8;
typedef struct {
    char b[8];
} UnkStruct_02079db8_2;

extern UnkStruct_02079db8 *func_02079350(void);
extern int func_02082240(void);
extern int func_0207cadc(void *a);
extern void func_020794d4(UnkStruct_02079db8 *e, int k);
extern void func_0207a2fc(void *self, UnkStruct_02079db8_2 *p, void *q);
extern void func_0207a308(void *self, void *p);
extern void func_0207a254(void *self);
extern void func_02079ef0(void *self, UnkStruct_02079db8_2 *b, int *c, UnkStruct_02079db8_2 *a, void *x);
extern void func_0207a02c(void *self, UnkStruct_02079db8_2 *b, int *c, UnkStruct_02079db8_2 *a, void *x, int lim);
extern void func_02079fc8(void *self, UnkStruct_02079db8_2 *a, int *d, UnkStruct_02079db8 *base);
extern void func_02079f60(void *self, UnkStruct_02079db8_2 *b, int *d, UnkStruct_02079db8 *base, int c);

void func_02079db8(void *self, void *a1)
{
    int lim;
    int m;
    UnkStruct_02079db8 *base;
    UnkStruct_02079db8_2 A;
    UnkStruct_02079db8_2 B;
    int c;
    int d;
    int i;

    base = func_02079350();
    c = 0;
    lim = func_02082240();
    m = func_0207cadc(a1);
    i = 0;
    d = 0;
    for (; i < 8; i++) {
        func_020794d4(&base[i], 3);
    }
    func_0207a2fc(self, &A, self);
    func_0207a308(self, self);
    func_0207a308(self, &B);
    m = m * 3;
    if (lim > (m >> 2)) {
        lim = m >> 2;
    }
    func_0207a254(self);
    func_02079ef0(self, &B, &c, &A, a1);
    func_0207a02c(self, &B, &c, &A, a1, lim);
    func_02079fc8(self, &A, &d, base);
    func_02079f60(self, &B, &d, base, c);
}
