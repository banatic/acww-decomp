/* func_020ae494 @ 0x020ae494, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void func_02099870(void);
extern int func_02094ffc(void);
extern unsigned char data_021f49e8;

int func_020ae494(signed char *param)
{
    if (param[4] != -1) {
        func_020984e8();
        func_02099870();
        if (func_02094ffc() == 1) {
            data_021f49e8 = 1;
            return 1;
        }
    }
    return 0;
}
