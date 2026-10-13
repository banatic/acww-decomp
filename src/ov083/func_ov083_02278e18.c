/* func_ov083_02278e18 @ 0x02278e18, 0x4c bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov083_02278e08(void *a, void *b);
extern void func_020861dc(void *a);
extern void func_02086834(void *a, int b);
extern void func_0209f128(void *a, int b);
extern int data_021f3aa4;
extern int data_021dc7a8;

int func_ov083_02278e18(void *p)
{
    if (func_ov083_02278e08(p, (char *) p + 0x654)) {
        return 1;
    }
    *(int *) ((char *) p + 0x654) = 0x258;
    {
        void *base = &data_021f3aa4;
        func_020861dc(base);
        func_02086834(base, 3);
        func_0209f128(&data_021dc7a8, 0xf);
    }
    return 1;
}
