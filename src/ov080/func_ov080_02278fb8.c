/* func_ov080_02278fb8 @ 0x02278fb8, 0x78 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern void func_ov080_02278f00(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_02054188(void *a, int b, int c);
extern int func_020984e8(int a);
extern int func_02099020(int a, int b);
extern void func_0203e2ec(void);

int func_ov080_02278fb8(void *p)
{
    if (func_0202ec58() == 0) {
        return 0;
    }
    func_ov080_02278f00(p, 0);
    func_02016764((char *) p + 0x334, p, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((char *) p + 0xec, 0xc, 0xe);
    (*(unsigned int *) ((char *) p + 0x4e8)) |= 2;
    if (func_02099020(func_020984e8(2), 1) == 0) {
        func_0203e2ec();
    }
    return 1;
}
