/* func_020b14ec @ 0x020b14ec, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020b15b0(int a, int b, int c);
extern void func_020b19a0(char *ptr, int n);
extern void func_020b1a0c(char *ptr, int n);

void func_020b14ec(int param1, int param2, int param3)
{
    char *base;
    base = func_020b15b0(param1, param2, param3);
    func_020b19a0(base, param2);
    func_020b1a0c(base + 0x4a * param2, param1);
    if (param3 != 0) {
        *(unsigned short *) (base + 0x4a2) |= (1 << param2);
    }
}
