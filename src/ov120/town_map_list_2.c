/* town_map_list_2: 5 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229abec @ 0x0229abec, 0x1c bytes, Thumb
 * func_ov120_0229abdc @ 0x0229abdc, 0x10 bytes, Thumb
 * func_ov120_0229abd0 @ 0x0229abd0, 0xc bytes, Thumb
 * func_ov120_0229ab20 @ 0x0229ab20, 0xb0 bytes, Thumb
 * func_ov120_0229aacc @ 0x0229aacc, 0x54 bytes, Thumb
 */

struct S_0229abdc {
    char pad_00[0x9a];
    unsigned short unk_9A;
};

struct UnkStruct_0229ab20 {
    char pad_00[0x98];
    unsigned short unk_98;
    unsigned short unk_9A;
    char pad_9C[0xa4 - 0x9c];
    unsigned char unk_A4;
};

struct UnkStruct_0229aacc {
    char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char unk_A5;
    unsigned char unk_A6;
    char pad_A7[0x5cd];
    unsigned int unk_674;
};

extern void func_ov120_0229a438(void *obj, unsigned int arg);
extern int func_ov120_0229a448(int a, int b);
extern int func_ov120_0229b14c(void *arg0);
extern void func_ov120_0229a428(void *obj, int arg);
extern int _s32_div_f(int a, int b);
extern int func_ov002_0220a58c(void *p, unsigned char a, unsigned char b);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov120_0229abec(unsigned char *obj, unsigned short value)
{
    *(unsigned short *) (obj + 0x98) = value;
    *(unsigned short *) (obj + 0x9A) = *(unsigned short *) (obj + 0x98);
    func_ov120_0229a438(obj, 0x10);
}

void func_ov120_0229abdc(struct S_0229abdc *self, unsigned short val)
{
    self->unk_9A = val;
    func_ov120_0229a438(self, 0x10);
}

int func_ov120_0229abd0(int a)
{
    return func_ov120_0229a448(a, 0x10);
}

void func_ov120_0229ab20(struct UnkStruct_0229ab20 *obj)
{
    int r4 = func_ov120_0229b14c((void *) obj);

    if (r4 == 0) {
        func_ov120_0229a428(obj, 0x10);
        obj->unk_A4 = 0;
        return;
    }

    if (obj->unk_98 == obj->unk_9A) {
        func_ov120_0229a428(obj, 0x10);
    } else if (obj->unk_98 < obj->unk_9A) {
        obj->unk_98 += 8;
        if (obj->unk_98 > obj->unk_9A) {
            obj->unk_98 = obj->unk_9A;
        }
    } else if (obj->unk_98 < 8) {
        obj->unk_98 = obj->unk_9A;
    } else {
        obj->unk_98 -= 8;
        if (obj->unk_98 < obj->unk_9A) {
            obj->unk_98 = obj->unk_9A;
        }
    }

    obj->unk_A4 = (unsigned char) _s32_div_f(obj->unk_98 * 0x58, r4);
}

int func_ov120_0229aacc(struct UnkStruct_0229aacc *obj)
{
    if (func_ov120_0229a448((int) obj, 8) == 0) {
        return 0;
    } else {
        if (func_ov002_0220a58c(&obj->unk_674, data_021f6c58, data_021f6c54) != 0) {
            obj->unk_A5 = data_021f6c54;
            obj->unk_A6 = obj->unk_A4;
            return 1;
        } else {
            return 0;
        }
    }
}
