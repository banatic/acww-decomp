/* func_ov107_0229c670 @ 0x0229c670, 0xb0 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
} UnkStruct_0229c670_2;
typedef struct {
    char pad_00[0x8e];
    short unk_8E;
} UnkStruct_0229c670;

extern int func_ov107_0229c354(void);
extern int func_ov003_0222ea84(int);
extern unsigned short func_ov107_0229d0f0(UnkStruct_0229c670_2 *, int);
extern int func_020644cc(int);
extern UnkStruct_0229c670 *func_020961a8(int);
extern void func_ov003_0222e898(unsigned char, int);
extern void func_ov003_0222eabc(int, int);
extern int func_ov003_02219b38(int);
extern void func_ov107_0229c628(UnkStruct_0229c670_2 *, unsigned char, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov107_0229caa8(UnkStruct_0229c670_2 *);

void func_ov107_0229c670(UnkStruct_0229c670_2 *o)
{
    volatile unsigned short v;
    unsigned int ok;
    unsigned short t1, t2;
    int h, y, r, d;

    h = func_ov107_0229c354();
    if (func_ov003_0222ea84(h) != 0) {
        return;
    }
    v = func_ov107_0229d0f0(o, o->unk_B9);
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
    func_ov107_0229c628(o, (unsigned char) d, r);
    func_ov002_02208098((void *) (o), 0x12);
    func_ov107_0229caa8(o);
}
