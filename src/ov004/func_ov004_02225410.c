/* func_ov004_02225410 @ 0x02225410, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_020a12e8(void);
extern int func_020644cc(int a);
extern int func_02099020(void *ctx, int a);
extern void func_02098ff8(void *ctx, int a);
extern int data_ov004_02254794;

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
