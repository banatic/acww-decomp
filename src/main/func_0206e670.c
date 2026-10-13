/* func_0206e670 @ 0x0206e670, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0340(void);
extern void func_02054094(void);
extern void func_02074904(int);
extern void func_020b9280(void);
extern void func_020e9548(void);
extern void func_0209d36c(void);
extern void func_0209dfa4(int);

void func_0206e670(int arg0)
{
    int r4 = arg0;
    func_020b0340();
    func_02054094();
    if (r4 != 0) {
        func_02074904(r4);
    }
    func_020b9280();
    func_020e9548();
    func_0209d36c();
    func_0209dfa4(r4);
}
