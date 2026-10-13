/* func_ov068_02271160 @ 0x02271160, 0x1f8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

extern void *func_ov003_02236164(int k);
extern int func_ov003_0221ac18(void *o);
extern int func_0200322c(void *a, void *b);
extern int func_ov003_0221b5e8(void);
extern int func_ov003_0221b5f0(void);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_ov003_02233c70(int a, int b);
extern void func_ov003_0223597c(int *out, int ang);
extern int func_020ea990(void *a, void *b);
extern int func_ov003_0221ac24(void *o, int *p);
extern void func_020550e4(void *p, int k);
extern int func_020644cc(int k);

extern int data_ov068_022786c0;
extern int data_ov068_022786c4;

void func_ov068_02271160(char *self)
{
    char *obj;
    int ang;
    int *q;
    int k;
    int t;
    int v3[3];
    int pos[3];
    int *p204;
    int lim;
    int a;
    int d;

    obj = (char *) func_ov003_02236164(*(int *) (self + 0x21c));
    p204 = (int *) (self + 0x204);
    if (obj != 0) {
        q = (int *) obj;
        q = (int *) ((int) q + 0x5c);
        lim = func_ov003_0221ac18(obj);
        ang = func_0200322c(q, p204);
        d = ang;
        pos[0] = *(int *) (obj + 0x5c);
        pos[1] = q[1];
        pos[2] = q[2];
        if ((data_ov068_022786c4 & 1) == 0) {
            t = func_ov003_0221b5e8();
            data_ov068_022786c0 = t - func_ov003_0221b5f0();
            data_ov068_022786c4 = data_ov068_022786c4 | 1;
        }
        lim = lim - FX_MulFunc(0x4cd, FX_Div(lim - func_ov003_0221b5f0(), data_ov068_022786c0));
        if (*(unsigned char *) (self + 0x24f) % 0x14 == 0) {
            a = (short) (func_ov003_02233c70(6, 1) * 2);
            ang = (short) (ang + a);
            *(short *) (self + 0x232) = a;
        } else {
            ang = (short) (ang + *(short *) (self + 0x232));
        }
        k = *(unsigned char *) (self + 0x24f);
        if (k % 4 == 0) {
            d = (short) (d + 0x38e);
        } else if (k % 2 == 0) {
            d = (short) (d - 0x38e);
        }
        *(short *) (self + 0x23a) = d;
        func_ov003_0223597c(v3, ang);
        pos[0] = pos[0] - FX_MulFunc(v3[0], 0x2666);
        pos[2] = pos[2] - FX_MulFunc(v3[2], 0x2666);
        a = func_020ea990(pos, p204);
        if (a < lim) {
            p204[0] = p204[0] - v3[0];
            p204[2] = p204[2] - v3[2];
        } else if (a > lim + 0x333) {
            p204[0] = p204[0] - FX_MulFunc(v3[0], 0x3000);
            p204[2] = p204[2] - FX_MulFunc(v3[2], 0x3000);
        } else {
            p204[0] = p204[0] - FX_MulFunc(v3[0], 0x2666);
            p204[2] = p204[2] - FX_MulFunc(v3[2], 0x2666);
        }
        if (func_ov003_0221ac24(obj, pos) == 0) {
            *(unsigned char *) (self + 0x251) = 5;
            func_020550e4(self + 0x50, 0);
            *(short *) (self + 0x232) = func_020644cc(0x14) + 0x28;
        }
    } else {
        *(unsigned char *) (self + 0x251) = 5;
        func_020550e4(self + 0x50, 0);
        *(short *) (self + 0x232) = func_020644cc(0x14) + 0x28;
    }
}
