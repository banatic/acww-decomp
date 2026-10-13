/* func_020a6104 @ 0x020a6104, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a617c(int a, int b, int c);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, char *q, int r);
extern void func_02073770(void *p, int r, int b);
extern void *data_020ccf94;

void func_020a6104(int a, int b, int c)
{
    if (c) {
        func_020a617c(a, b, 6);
    } else {
        if (b == 0) {
            func_020a617c(a, 0, 6);
        } else {
            char v = 6;
            void *p = data_020ccf94;
            func_02073820(p);
            func_020737f0(p, &v, 1);
            func_02073770(p, 1, b);
            func_020a617c(a, b, 7);
        }
    }
}
