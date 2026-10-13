/* func_ov104_0229d624 @ 0x0229d624, 0x80 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229d8a8(unsigned char *, unsigned char);
extern int func_ov104_0229d858(unsigned char *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa60(unsigned char *, int, int);
extern int func_ov104_0229da80(unsigned char *, unsigned char);
extern int func_ov104_0229da70(unsigned char *, unsigned char);
extern int func_ov104_0229da38(unsigned char *, unsigned char);
extern void func_ov094_0229b9b4(unsigned char *, unsigned char *, int);

void func_ov104_0229d624(unsigned char *self)
{
    int v6;
    int v4;
    int v2;

    v6 = func_ov104_0229d8a8(self, self[0xb6]) - 0x6d;
    v4 = func_ov104_0229d858(self, self[0xb6]) - 0x78;
    if (func_0206fe54()) {
        v4 -= 8;
    }
    func_0208aa60(self + 0x23b8, v6, v4);

    if (func_ov104_0229da80(self, self[0xb6]) == 0) {
        if (func_ov104_0229da70(self, self[0xb6]) == 0) {
            return;
        }
    }

    v2 = func_ov104_0229da38(self, self[0xb6]);
    func_ov094_0229b9b4(self + 0x0d58, self + 0x23b8, v2);
}
