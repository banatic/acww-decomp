/* func_ov099_0229d518 @ 0x0229d518, 0xa8 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208008(char *arg0);
extern int func_ov099_0229c2c4(unsigned char *, int);
extern void func_ov099_0229c9d0(unsigned char *);
extern void func_ov099_0229c6dc(unsigned char *);
extern int func_ov099_0229cf30(unsigned char *, int);
extern int func_ov099_0229cc74(unsigned char *, int);
extern void func_ov099_0229c56c(unsigned char *, int);
extern void func_ov099_0229c520(unsigned char *, int);
extern void func_ov099_0229c928(unsigned char *);
extern int func_ov002_02207d24(unsigned char *, int);
extern void func_ov002_02207d00(unsigned char *);

extern struct {
    unsigned char pad[2];
    unsigned short flag;
} data_021fbe40;

void func_ov099_0229d518(unsigned char *self)
{
    int ret = func_ov002_02208008((char *) self);
    unsigned short flag;
    unsigned char b;

    if (func_ov099_0229c2c4(self, ret) != 0) {
        func_ov099_0229c9d0(self);
        func_ov099_0229c6dc(self);
        func_ov002_02207d24(self + 0x218c, 0);
        return;
    }

    flag = data_021fbe40.flag;

    if ((flag & 1) != 0) {
        b = self[0x2907];
        if (func_ov099_0229cf30(self, b) != 0) {
            b = self[0x2907];
            if (func_ov099_0229cc74(self, b) != 0) {
                b = self[0x2907];
                func_ov099_0229c56c(self, b);
            } else {
                b = self[0x2907];
                func_ov099_0229c520(self, b);
            }
        }
    } else {
        if ((flag & 2) != 0) {
            b = self[0x2906];
            func_ov099_0229c56c(self, b);
        } else {
            func_ov099_0229c928(self);
            func_ov002_02207d00(self + 0x218c);
        }
    }
}
