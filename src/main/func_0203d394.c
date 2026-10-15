/* func_0203d394 @ 0x0203d394, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_0209964c(int);
extern int func_0203d4b8(void);
extern int func_0203d278(void *);
extern int func_0203d4a8(void);
extern void func_0203d32c(int);
extern void func_0203d320(int);
extern int func_0203d264(int);
extern int func_0203d470(void);
extern void func_0203d300(int);
extern void func_0203d2f4(int);
extern int func_0203d250(int);
extern int func_0203d438(void);
extern void func_0203d2d4(int, int);
extern void func_0203d35c(int, int *);
extern void func_0203d28c(int);
extern void func_0203d34c(int, int *);

void func_0203d394(void)
{
    int r5;
    int r4;
    int sp0;

    r5 = func_0209964c((int) func_020984e8());
    r4 = func_0203d4b8();
    if (func_0203d278((void *) r4) != 0) {
        if (func_0203d4a8() == 1) {
            func_0203d32c(r5);
        } else {
            func_0203d320(r5);
        }
    }
    if (func_0203d264(r4) != 0) {
        if (func_0203d470() == 1) {
            func_0203d300(r5);
        } else {
            func_0203d2f4(r5);
        }
    }
    if (func_0203d250(r4) != 0) {
        func_0203d2d4(r5, func_0203d438());
    }
    func_0203d35c(r5, &sp0);
    func_0203d28c(r4);
    func_0203d34c(r4, &sp0);
}
