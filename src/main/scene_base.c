/* scene_base: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02015c3c @ 0x02015c3c, 0x3e bytes, Thumb
 * func_02015bfc @ 0x02015bfc, 0x40 bytes, Thumb
 * func_02015b9c @ 0x02015b9c, 0x60 bytes, Thumb
 */

extern int func_02015d44(void);
extern int func_02095794(int);
extern int func_0200322c(int a, void *b);
extern void *func_02096190(int a);
extern int func_02095518(int a, int b, int c);
extern int func_02095a8c(int, int);
extern void func_02095eec(int, int);
extern void *func_02015da0(void *self, int param);
extern void func_0201ad18(void *p, int a, int b, void *c, int d, int e, int f, int g);
extern unsigned char data_021fbee8[];

int func_02015c3c(int a, int b)
{
    int r5 = func_02015d44();
    int cond = func_02095794(r5);
    if (cond != 0) {
        int r4 = func_0200322c(cond, (char *) b + 0x5c);
        int diff = (short) (r4 - *(short *) ((char *) func_02096190(4) + 0x8e));
        return func_02095518(0, diff, r5);
    }
    return cond;
}

void func_02015bfc(int arg0, void *arg1)
{
    int val = func_02015d44();
    int flag = func_02095794(val);
    if (flag) {
        void *p = (char *) arg1 + 0x5c;
        int res = func_0200322c(flag, p);
        func_02095518(0, 0, val);
        func_02095a8c(res, val);
        func_02095eec(1, val);
    }
}

void func_02015b9c(void *self)
{
    void *a;
    void *b;
    unsigned char state;

    a = func_02015da0(self, 0);
    if (a == 0) {
        return;
    }

    state = ((unsigned char *) self)[0x54];
    switch (state) {
        case 1:
            b = func_02015da0(self, state);
            if (b != 0) {
                func_0201ad18((char *) b + 0x3b0, 2, 0, a, (unsigned int) data_021fbee8, 4, 0, 0);
            }
            break;
        case 2:
            func_02015c3c((int) self, (int) a);
            break;
    }
}
