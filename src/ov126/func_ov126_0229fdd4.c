/* func_ov126_0229fdd4 @ 0x0229fdd4, 0x54 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_ov126_022a027c(void *param, int n);
extern void func_ov095_0229bf3c(void *param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov126_022a0a50(void *param);

int func_ov126_0229fdd4(void *param)
{
    if ((data_021fbe40 & 2) == 0) {
        return 0;
    }

    if (func_ov126_022a027c(param, 0) != 0) {
        func_ov095_0229bf3c((char *) param + 0x19c);
        ((unsigned char *) param)[0xae] = ((unsigned char *) param)[0x8d];
        func_ov002_02208098((void *) (param), 0xc);
    } else {
        func_ov126_022a0a50(param);
    }
    return 1;
}
