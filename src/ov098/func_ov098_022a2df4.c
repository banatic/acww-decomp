/* func_ov098_022a2df4 @ 0x022a2df4, 0xa8 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    char pad_00[0xb6];
    unsigned char unk_B6;
} Obj_ov096_022a23e8;
typedef struct {
    char pad_00[0x8e];
    short unk_8E;
} UnkStruct_022a2df4;

extern int func_ov096_0229cbbc(void);
extern int func_ov003_0222ea84(int);
extern unsigned short func_ov096_0229f0dc(Obj_ov096_022a23e8 *, int);
extern int func_020644cc(int);
extern UnkStruct_022a2df4 *func_020961a8(int);
extern void func_ov003_0222e898(unsigned char, int);
extern void func_ov003_0222eabc(int, int);
extern int func_ov003_02219b38(int);
extern void func_ov098_022a2dac(Obj_ov096_022a23e8 *, unsigned char, int);
extern unsigned char *func_ov096_0229f860(Obj_ov096_022a23e8 *);

int func_ov098_022a2df4(Obj_ov096_022a23e8 *o)
{
    volatile unsigned short v;
    unsigned int ok;
    unsigned short t1, t2;
    int h, y, r, d;
    int status;

    h = func_ov096_0229cbbc();
    status = func_ov003_0222ea84(h);
    if (status != 0) {
        return status;
    }
    v = func_ov096_0229f0dc(o, o->unk_B6);
    ok = 0;
    t1 = v;
    t2 = v;
    if (t2 >= 0x12b0 && t1 <= 0x12e7) {
        ok = 1;
    }
    if (ok > 0) {
        d = t1 - 0x12b0;
    } else {
        d = -1;
    }
    r = (unsigned char) func_020644cc(0x3c);
    y = (short) (0xb6 * (r - 0x1e));
    y = (short) (y + func_020961a8(4)->unk_8E);
    func_ov003_0222e898((unsigned char) d, h);
    func_ov003_0222eabc(h, y);
    func_ov003_02219b38(0);
    func_ov098_022a2dac(o, (unsigned char) d, r);
    return (int) func_ov096_0229f860(o);
}
