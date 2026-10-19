/* func_ov112_0229ffdc @ 0x0229ffdc, 0x4c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov112_0229f45c(void *object, unsigned char flags, int mode);
extern int func_ov112_0229fe70(void *this, int n);
extern void func_0200467c(int cmd);
extern void func_02077ed4(void *ptr);
extern void func_ov112_0229efe8(void *this);
extern int func_020984e8(void);
extern int func_02099640(int);
extern void func_0209a8c4(void *);

void func_ov112_0229ffdc(void *this)
{
    func_ov112_0229f45c(this, 10, 3);
    if (func_ov112_0229fe70(this, 0x2000) != 0) {
        func_0200467c(0x28);
    } else {
        func_02077ed4((char *) this + 0xC4);
        func_0200467c(0x27);
        func_ov112_0229efe8(this);
        func_0209a8c4((void *) func_02099640((int) func_020984e8()));
    }
}
