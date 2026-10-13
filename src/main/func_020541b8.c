/* func_020541b8 @ 0x020541b8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054a94(unsigned int, unsigned int);
extern void func_02054a34(unsigned int, unsigned int);
extern void func_020545b0(unsigned int, unsigned int);

void func_020541b8(unsigned int param0, unsigned int param1, unsigned int param2)
{
    unsigned int i;
    for (i = param1; i <= param2; i++) {
        func_02054a94(param0, i);
        func_02054a34(param0, i);
        func_020545b0(param0, i);
    }
}
