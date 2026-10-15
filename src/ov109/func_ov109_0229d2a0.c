/* func_ov109_0229d2a0 @ 0x0229d2a0, 0x30 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern unsigned char data_021fbdd8;

void func_ov109_0229d2a0(int arg0)
{
    if (func_0206f56c() != 0) {
        func_ov002_02208098(arg0, 4);
    } else {
        if (data_021fbdd8 == 0) {
            func_ov002_02208098(arg0, 4);
        }
    }
}
