/* func_ov004_0222adcc @ 0x0222adcc, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_020ccf94;
extern int func_02073908(char *a, int b);
extern void func_020114b0(void *p, int v, int a, int b, int c);
extern void func_0200f554(void *self);

void func_ov004_0222adcc(char *self)
{
    char *q = self + 0x7d4;
    char *p;
    int v;

    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        p = self + 0x5c;
        if ((*(short *) (q + 8) & 0x4000) != 0) {
            v = *(int *) q;
        } else {
            p += 8;
            v = *(int *) (q + 4);
        }
        func_020114b0(p, v, 0x399, 0x1ec, 0x31);
    } else {
        func_0200f554(self);
    }
}
