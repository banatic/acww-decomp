/* func_ov055_022604f4 @ 0x022604f4, 0x20 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern char data_021d11c4;
extern char SDK_OVERLAY_ov067_ID;
extern void func_02077b9c(char *);
extern int func_02077b70(char *, int);

void func_ov055_022604f4(void *receiver)
{
    func_02077b9c(&data_021d11c4);
    func_02077b70(&data_021d11c4, (int) &SDK_OVERLAY_ov067_ID);
}
