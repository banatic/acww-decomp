/* field_actor_room_states2_9: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222ae54 @ 0x0222ae54, 0x50 bytes, Thumb
 * func_ov004_0222ae34 @ 0x0222ae34, 0x20 bytes, Thumb
 * func_ov004_0222adcc @ 0x0222adcc, 0x68 bytes, Thumb
 */

extern void func_ov004_0222af30(void *a, unsigned char *b, int *c, int *d);
extern int func_ov004_0222af6c(int self, int b, int c, int d, int e, int f, short g);
extern void func_020110a0(void *object, short *values);
extern char *data_020ccf94;
extern int func_02073908(char *a, int b);
extern void func_020114b0(void *p, int v, int a, int b, int c);
extern int func_0200f554(void *self);

void func_ov004_0222ae54(char *self, short arg)
{
    unsigned char b;
    int c, d;

    if (*(int *) (self + 0x7f0) == 0xf) {
        *(short *) (self + 0xc84) = arg;
    } else {
        func_ov004_0222af30(self + 0x8f0, &b, &c, &d);
        func_ov004_0222af6c((int) self, b, c, d, 0, 6, arg);
    }
}

void func_ov004_0222ae34(char *self, int stateId)
{
    const int *src = (const int *) (self + 0x7d4);
    int *dst = (int *) (self + 0x5c);
    dst[0] = src[0];
    dst[2] = src[1];
    func_020110a0(self, (short *) (src + 2));
}

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
