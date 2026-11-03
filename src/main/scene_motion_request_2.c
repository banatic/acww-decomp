/* scene_motion_request_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02019d78 @ 0x02019d78, 0x1a bytes, Thumb
 * func_02019d70 @ 0x02019d70, 0x6 bytes, Thumb
 * func_02019d0c @ 0x02019d0c, 0x64 bytes, Thumb
 * func_02019cc8 @ 0x02019cc8, 0x42 bytes, Thumb
 */

typedef struct UnkStruct_02019d0c_2 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char pad_14[4];
    short unk_18;
    short unk_1A;
    unsigned short unk_1C;
    unsigned short unk_1E;
} UnkStruct_02019d0c_2;

typedef struct UnkStruct_02019d0c {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02019d0c_2 sub;
} UnkStruct_02019d0c;

extern void func_02019ea0(void *arg0);

void func_02019d70(int *p, int a, int b);

void func_02019d78(void *arg0)
{
    void *r4;

    r4 = arg0;
    func_02019d70((int *) r4, 0x16, 0);
    r4 = (void *) ((unsigned int) r4 + 0x2c);
    func_02019ea0(r4);
}

void func_02019d70(int *p, int a, int b)
{
    p[9] = a;
    p[10] = b;
}

int func_02019d0c(UnkStruct_02019d0c *s, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                  unsigned short argF, unsigned short argG)
{
    int result = 0;
    if (value >= s->unk_28 || s->unk_28 == 3) {
        if (kind != 0xc) {
            UnkStruct_02019d0c_2 *sub = &s->sub;
            short c;
            short b;
            func_02019d70((int *) s, kind, value);
            func_02019ea0((void *) sub);
            sub->unk_04 = r3val;
            sub->unk_08 = argA;
            if (argD == 0 && argE == 0) {
                sub->unk_0C = r3val;
                sub->unk_10 = argA;
            } else {
                sub->unk_0C = argD;
                sub->unk_10 = argE;
            }
            c = argC;
            b = argB;
            sub->unk_18 = c;
            sub->unk_1A = b;
            sub->unk_1C = argF;
            sub->unk_1E = argG;
            result = 1;
        }
    }
    return result;
}

int func_02019cc8(void *self, int p1, int p2, int p3, int p5, unsigned short p6)
{
    int result = 0;
    if (func_02019d0c((UnkStruct_02019d0c *) self, 7, p1, 0, 0, (short) p2, (short) p3, 0, 0, p6, 0)) {
        *(int *) ((char *) self + 0x40) = p5;
        result = 1;
    }
    return result;
}
