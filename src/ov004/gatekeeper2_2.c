/* gatekeeper2_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02225410 @ 0x02225410, 0x60 bytes, Thumb
 * func_ov004_022253c8 @ 0x022253c8, 0x46 bytes, Thumb
 */

extern void *func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_020a12e8(void);
extern int func_020644cc(int a);
extern int func_02099020(void *ctx, int a);
extern void func_02098ff8(void *ctx, int a);
extern int data_ov004_02254794;
extern void func_020157c8(void *self, int a, int b);
extern int func_02015828(void *self, int a);
extern void func_ov004_022251a4(void *self, int a);

void func_ov004_02225410(void *a, char *out)
{
    void *ctx = func_020984e8();

    if (func_0202e9fc() == 0 || func_020a12e8() != 0) {
        out[4] = (char) (func_020644cc(3) + 8);
    } else {
        if (func_02099020(ctx, 0x1b) == 0) {
            out[4] = 0;
            func_02098ff8(ctx, 0x1b);
        } else {
            out[4] = (char) (func_020644cc(4) + 4);
        }
    }
    *(int *) out = data_ov004_02254794;
}

void func_ov004_022253c8(char *self)
{
    unsigned char v = self[0x1e];

    switch (v) {
        case 0x1a:
            func_020157c8(self, 0x1f, 0);
            func_02015828(self, 2);
            func_ov004_022251a4(self, 3);
            break;
        case 0x17:
            func_020157c8(self, 9, 0);
            func_02015828(self, 2);
            func_ov004_022251a4(self, 2);
            break;
    }
}
