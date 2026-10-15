/* func_020a7d20 @ 0x020a7d20, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a941c(void *param);
extern void func_020edb3c(void *param);

extern unsigned char data_020e3e44[];
extern unsigned char data_020e3e68[];

void *func_020a7d20(void *param)
{
    *(volatile unsigned int *) param = (unsigned int) data_020e3e44;
    *(volatile unsigned int *) param = (unsigned int) data_020e3e68;
    func_020a941c(param);
    func_020edb3c(param);
    return param;
}
