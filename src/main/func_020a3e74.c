/* func_020a3e74 @ 0x020a3e74, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a0284(int, int);
extern void func_02097b24(void);
extern void func_020b1130(void);
extern void func_0209fbec(void);
extern unsigned char *data_020ccf94;

void func_020a3e74(int param)
{
    func_020a0284(param, 1);
    if (data_020ccf94[0x6c] == 1) {
        func_02097b24();
        func_02097b24();
        func_020b1130();
        func_0209fbec();
    }
}
