/* func_0203e4e0 @ 0x0203e4e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a6d24(void);
extern void func_020a6ce4(void);
extern void func_020a529c(void);
extern void func_01ffd418(int, int);
extern int data_021f42f4;

void func_0203e4e0(int a, int b)
{
    func_020a6d24();
    func_020a6ce4();
    if (data_021f42f4) {
        func_020a529c();
    }
    func_01ffd418(a, b);
}
