/* func_ov126_0229fd64 @ 0x0229fd64, 0x70 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov095_0229cf64(void *ptr, int val);
extern int func_ov126_022a03dc(void *ptr, int val);
extern void func_ov095_0229c8e4(void *ptr, int val);
extern void func_ov126_0229ff0c(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

int func_ov126_0229fd64(void *param)
{
    if (!(data_021fbe40[1] & 0x100)) {
        return 0;
    }

    if (func_ov095_0229cf64((char *) param + 0x19c, 0xc)) {
        return 0;
    }

    func_ov126_022a03dc(param, 0x119);
    func_ov095_0229c8e4((char *) param + 0x19c, 0x10a);
    func_ov126_0229ff0c(param);

    *((unsigned char *) param + 0xae) = *((unsigned char *) param + 0x8d);

    func_ov002_02208098((void *) (param), 0xe);
    return 0;
}
