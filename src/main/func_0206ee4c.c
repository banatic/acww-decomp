/* func_0206ee4c @ 0x0206ee4c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f278(void);
extern void func_02001ca0(int, int, int, int);
extern void func_0206f150(void);
extern unsigned short data_021cfc20;

int func_0206ee4c(void)
{
    if (func_0206f278() == 0) {
        func_02001ca0(1, 0, 255, 192);
        data_021cfc20 = 3;
        func_0206f150();
    }
    return 1;
}
