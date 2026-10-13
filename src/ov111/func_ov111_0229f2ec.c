/* func_ov111_0229f2ec @ 0x0229f2ec, 0x6c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern int func_ov095_0229cf64(void *ptr, int num);
extern void func_ov111_0229f730(void *ptr, int num);
extern void func_ov095_0229c8e4(void *ptr, int num);
extern void func_ov111_0229f10c(void *ptr);
extern void func_ov002_02208098(void *ptr, int num);

int func_ov111_0229f2ec(unsigned char *arg)
{
    if ((data_021fbe40[1] & 0x100) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64((void *) (arg + 0xac), 0xc) != 0) {
        return 0;
    }
    func_ov111_0229f730(arg, 0x119);
    func_ov095_0229c8e4((void *) (arg + 0xac), 0x10a);
    func_ov111_0229f10c(arg);
    arg[0x98] = arg[0x8d];
    func_ov002_02208098(arg, 0xc);
    return 1;
}
