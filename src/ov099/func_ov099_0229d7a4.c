/* func_ov099_0229d7a4 @ 0x0229d7a4, 0x70 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_02207ce4(void *, int);
extern void func_ov002_02207d00(void *);
extern int func_ov099_0229c2ac(void *, int);
extern int func_ov099_0229cadc(void);
extern int func_ov099_0229cac8(void *, int);
extern void func_ov099_0229d004(void *, unsigned char);
extern void func_ov099_0229c3e0(void *, unsigned char);

void func_ov099_0229d7a4(unsigned char *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
        func_ov002_02207ce4(self + 0x218c, 0x3c);
    } else {
        if (func_ov099_0229c2ac(self, 4) != 0) {
            asm {
                mov r0, self
            }
            if (func_ov099_0229cadc() != 0)
            {
                func_ov099_0229d004(self, self[0x2904]);
                return;
            }
            if (func_ov099_0229cac8(self, 9) != 0) {
                func_ov099_0229c3e0(self, self[0x2904]);
                return;
            }
        }
        func_ov002_02207d00(self + 0x218c);
    }
}
