/* func_ov004_0222bd6c @ 0x0222bd6c, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int a, int b);
extern void func_020109fc(void *self, int a, int b, int c);
extern void func_ov004_0222bdec(void *w, int k);
extern int func_0203e110(void);
extern int data_020ccf94;
void func_ov004_0222bd6c(unsigned char *self, unsigned char *p, int m)
{
    unsigned char *q, *w;
    q = p + 0xc;
    w = self + 0x7d4;
    if (*(int *) (self + 0x704) != 0x11) {
        if (m == 0xf || m == 0xd || func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
            func_020109fc(self, 0x11, 0, 0);
        } else {
            func_020109fc(self, 0x11, 3, 0);
        }
    }
    func_ov004_0222bdec(w, *q);
    if (*w == 0) {
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
            func_0203e110();
        }
    }
}
