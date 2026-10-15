/* func_ov112_022a05b0 @ 0x022a05b0, 0x70 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov095_0229cf64(void *ptr, int val);
extern int func_ov112_022a03ac(void *ptr, int val);
extern void func_ov095_0229c8e4(void *ptr, int val);
extern void func_ov112_0229f2bc(void *ptr);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);

int func_ov112_022a05b0(void *param)
{
    if (!(data_021fbe40[1] & 0x100)) {
        return 0;
    }

    if (func_ov095_0229cf64((char *) param + 0x384, 0xc)) {
        return 0;
    }

    func_ov112_022a03ac(param, 0x119);
    func_ov095_0229c8e4((char *) param + 0x384, 0x10a);
    func_ov112_0229f2bc(param);

    *((unsigned char *) param + 0xc1) = *((unsigned char *) param + 0x8d);

    func_ov002_02208098(param, 0xf);
    return 1;
}
