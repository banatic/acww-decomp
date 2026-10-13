/* func_ov112_022a0b84 @ 0x022a0b84, 0x64 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *, unsigned char);
extern int func_ov095_0229bf0c(void *);
extern int func_ov112_022a02f4(void *, int);
extern int func_ov112_0229fe70(void *, int);
extern void func_ov112_0229f2bc(void *);
extern void func_ov112_0229f3e0(void *);
extern void func_ov112_022a0028(void *);

void func_ov112_022a0b84(void *this)
{
    if ((data_021fbe40 & 2) == 0) {
        func_ov002_02208098(this, ((char *) this)[0xc1]);
    } else {
        if (func_ov095_0229bf0c((char *) this + 0x384) != 0) {
            if (func_ov112_022a02f4(this, 0) != 0) {
                if (func_ov112_0229fe70(this, 0x800) != 0) {
                    func_ov112_0229f2bc(this);
                }
            } else {
                func_ov112_0229f3e0(this);
                func_ov112_022a0028(this);
            }
        }
    }
}
