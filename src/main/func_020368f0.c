/* func_020368f0 @ 0x020368f0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_02037260(void *ptr);
extern void func_02036fec(void *ptr);
extern void func_02036ec8(void *ptr);

void func_020368f0(void *param)
{
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        func_02037260((char *) param + 4);
        func_02036fec((char *) param + 0x18);
        func_02036ec8((char *) param + 0x24);
    }
}
