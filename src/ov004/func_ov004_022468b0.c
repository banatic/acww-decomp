/* func_ov004_022468b0 @ 0x022468b0, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6730(void);
extern int func_020b6760(void);
extern int func_020b65c4(void);
extern char data_ov004_0224c664[];
extern char data_ov004_0224be64[];
extern char data_ov004_0224c264[];

char *func_ov004_022468b0(void)
{
    if (func_020b6730() != 0) {
        return data_ov004_0224c664 + (func_020b6760() << 10);
    }
    if (func_020b65c4() == 0xa) {
        return data_ov004_0224be64;
    }
    return data_ov004_0224c264;
}
