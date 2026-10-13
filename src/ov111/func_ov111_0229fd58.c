/* func_ov111_0229fd58 @ 0x0229fd58, 0x98 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9034(int a, int b, int c);
extern int func_ov111_0229f4dc(void *p);
extern void func_02051608(void *p, int a, int b, int c, int d);

typedef struct {
    unsigned char pad_00[0x2c];
    int unk_2C;
    unsigned char _pad1[8];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[22];
    int unk_50;
    unsigned char pad_54[1];
    unsigned char unk_55;
} ObjA;

typedef struct {
    unsigned char pad_00[0x9f];
    unsigned char unk_9F;
    unsigned char unk_A0;
    unsigned char _pad1[7];
    ObjA *a8;
} UnkStruct_0229fd58;

void func_ov111_0229fd58(UnkStruct_0229fd58 *p)
{
    if (p->a8 == 0) {
        p->a8 = func_020a9034(0x13d, 0x15, 2);
        if (p->a8 != 0) {
            p->a8->unk_2C = 3;
            p->a8->unk_50 = 1;
            p->a8->unk_55 = 0;
            p->a8->unk_39 = 2;
            p->a8->unk_38 = 1;
            if (func_ov111_0229f4dc(p) != 0) {
                unsigned char b = p->unk_A0;
                unsigned char a = p->unk_9F;
                int min;
                int diff;
                if (a > b) {
                    min = b;
                    diff = a - b;
                } else {
                    min = a;
                    diff = b - a;
                }
                func_02051608(p->a8, 2, 1, min, diff);
            }
        }
    }
}
