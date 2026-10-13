/* func_ov004_02226aac @ 0x02226aac, 0x14c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02226aac {
    int a;
    int b;
    int c;
};
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_020b22a0(void);
extern int func_0200ee0c(void *self);
extern int func_020b67d4(void);
extern int func_020b6680(void);
extern int func_02073908(int a, int b);
extern void func_ov004_02226c00(void *dst, int a, int c);
extern void func_0200f328(void *self, int msg);
extern void func_020b220c(void);
extern void func_ov004_02226c08(void *dst, struct UnkStruct_02226aac t, int a, int n, unsigned char k);
extern void func_0201107c(void *self, void *p);
extern void func_0200f27c(void *self, int a);
extern int data_020ccf94;
extern int data_ov004_02254af4;
void func_ov004_02226aac(unsigned char *self, unsigned char *p)
{
    unsigned char *w;
    struct UnkStruct_02226aac t;
    int msg, n;
    int k;
    unsigned char *w2;
    struct UnkStruct_02226aac *q, *s;

    q = (struct UnkStruct_02226aac *) (p + 0xc);
    w = self + 0x7d4;
    func_020109fc(self, 1, 0, 0);
    n = 0;
    *(int *) (self + 0x2e0) = n;
    msg = n;
    k = func_020b22a0();
    *(int *) (self + 0x7f8) = 1;
    switch (k) {
        case 2:
            if ((func_0200ee0c(self) != 0 && func_020b67d4() != 0) || func_020b6680() != 0) {
                n = 0x14;
                msg = 0x4ca;
                *(int *) (self + 0x7f8) = 0;
            } else {
                msg = 0x4cb;
            }
            break;
        case 1:
            msg = 0x4d2;
            n = 0x14;
            *(int *) (self + 0x7f8) = 0;
            break;
        case 0:
        case 3:
            break;
    }
    w2 = self + 0x8f0;
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        s = (struct UnkStruct_02226aac *) (self + 0x5c);
        t.a = s->a;
        t.b = s->b;
        t.c = s->c;
        func_ov004_02226c00(w2, t.a, t.c);
        *(int *) (self + 0x64) = *(int *) (self + 0x64) + 0x6000;
    } else {
        if (msg != 0) {
            func_0200f328(self, msg);
            if (msg == 0x4cb) {
                func_020b220c();
            }
        }
        t.a = q->a;
        t.b = q->b;
        t.c = q->c;
        *(int *) (self + 0x64) = t.c + 0x6000;
    }
    func_ov004_02226c08(w, t, 0x400, n, (unsigned char) k);
    if (*(int *) (self + 0x7f8) == 1) {
        func_0201107c(self, &data_ov004_02254af4);
        *(int *) (w + 0xc) = 0x400;
    }
    func_0200f27c(self, 5);
}
