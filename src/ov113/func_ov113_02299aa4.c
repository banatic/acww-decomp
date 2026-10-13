/* func_ov113_02299aa4 @ 0x02299aa4, 0x1a0 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0xd];
    volatile unsigned char unk_9A;
    unsigned char unk_9B;
    unsigned char pad_9C;
    unsigned char unk_9D;
} UnkStruct_02299aa4;

extern int RtcSendPxiCommand(int cmd);
extern void func_ov113_02299a80(UnkStruct_02299aa4 *o);
extern void func_ov113_02299c44(UnkStruct_02299aa4 *o, int a);
extern void func_ov113_02299d84(UnkStruct_02299aa4 *o, int a);
extern void func_ov113_02299d94(UnkStruct_02299aa4 *o, int a);
extern void func_ov002_022080a0(UnkStruct_02299aa4 *o, int a);
extern __arm void *func_020ee45c(UnkStruct_02299aa4 *o);
extern void func_ov092_02299324(void *p, int a, int b);

int func_ov113_02299aa4(UnkStruct_02299aa4 *o)
{
    unsigned int v;
    unsigned int n;
    unsigned int cur;
    void *p;

    func_ov113_02299a80(o);
    v = o->unk_9B;
    switch (v) {
        case 2:
            RtcSendPxiCommand(0x29);
        case 3:
            func_ov113_02299c44(o, 1);
            o->unk_8C = 3;
            func_ov002_022080a0(o, 1);
            p = func_020ee45c(o);
            if (o->unk_9B == 3) {
                func_ov092_02299324(p, 0x43, 0);
                RtcSendPxiCommand(0x12);
            } else {
                func_ov092_02299324(p, 1, 1);
            }
            return 1;
        case 4:
            if (o->unk_9D > o->unk_9A + 1) {
                o->unk_9A = o->unk_9A + 1;
                func_ov113_02299c44(o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
        case 5:
            if (o->unk_9A != 0) {
                o->unk_9A = o->unk_9A - 1;
                func_ov113_02299c44(o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
        case 1:
            if (o->unk_9A != o->unk_9D - 1) {
                o->unk_9A = o->unk_9D - 1;
                func_ov113_02299c44(o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
        case 0:
            if (o->unk_9A != 0) {
                o->unk_9A = 0;
                func_ov113_02299c44(o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
    }
    if (v >= 6 && v <= 0x14) {
        n = (unsigned char) (v - 6);
        cur = o->unk_9A;
        if (n == cur) {
            return 0;
        }
        if (cur < n) {
            func_ov113_02299d94(o, 0x40);
        } else {
            func_ov113_02299d84(o, 0x40);
        }
        o->unk_9A = n;
        o->unk_8C = 5;
        func_ov002_022080a0(o, 1);
        return 1;
    }
    return 0;
}
