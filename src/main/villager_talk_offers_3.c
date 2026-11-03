/* villager_talk_offers_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02029264 @ 0x02029264, 0x4e bytes, Thumb
 * func_0202913c @ 0x0202913c, 0x128 bytes, Thumb
 */

#include "types.h"

struct Pair {
    int a;
    int b;
};

struct ST {
    int pad_00[8];
    u8 a;
    u8 b;
    u8 pad_22[2];
};

struct UnkStruct_0202913c {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc];
    int unk_100;
};

extern void func_02015ea0(int a, int b, int c);
extern void func_02015fb0(int a, int b, int c, int d, int e, int f);
extern int data_020c8924;
extern int data_020c8928;
extern struct Pair data_020d8de8;
extern struct Pair data_020d8df8;
extern int func_0201cddc(int a);
extern int func_0209bd44(void *a);
extern int func_0209bc40(void *a);
extern int func_0208150c(int a);
extern int func_0209aebc(void *a, int b);
extern int func_0209bba0(void *a);
extern void func_0201cfb4(struct UnkStruct_0202913c *a, struct ST *st);
extern void func_0201cf90(struct UnkStruct_0202913c *a, struct ST *st, int idx, int w, int h, void *str);
extern void func_0201cf74(struct UnkStruct_0202913c *a, struct ST *st, int idx, void *data, void *str);
extern void func_0201cec8(struct UnkStruct_0202913c *a, struct ST *st);
extern void func_0202da74(struct UnkStruct_0202913c *a, struct Pair p);
extern void func_02068388(int a, int b);
extern unsigned char data_021c1d6c[];
extern unsigned char data_021c1e14[];
extern unsigned char data_021c307c[];

void func_02029264(int a, unsigned char *p)
{
    unsigned int b2;
    b2 = p[2];
    if (b2 >= 12) {
        b2 -= 12;
    }
    if (b2 == 0) {
        b2 = 12;
    }
    func_02015ea0(a, p[3], 0);
    func_02015fb0(a, b2, 1, 2, 0, 0);
    func_02015fb0(a, p[1], 2, 2, 6, 9);
}

int func_0202913c(struct UnkStruct_0202913c *param0, int param1, char *param2, unsigned int index)
{
    char *a;
    char *b;
    int ok;
    struct ST st;

    a = param2 + 0xa4;
    b = a + 0x10;
    ok = 0;

    if (func_0201cddc(param0->unk_100) == 0xb) {
        if (func_0209bd44(b) != 0) {
            if (func_0209bc40(b) == 0x15) {
                if (func_0209aebc(a, func_0208150c(param1)) != 0) {
                    if (func_0209bba0(b) == 0) {
                        func_0201cfb4(param0, &st);
                        func_0201cf90(param0, &st, 0, 0x30, 0x30, (void *) data_021c307c);
                        func_0201cf74(param0, &st, 1, &data_020c8924, (void *) data_021c1d6c);
                        st.a = 2;
                        st.b = st.a - 1;
                        func_0201cec8(param0, &st);
                        func_0202da74(param0, data_020d8df8);
                        func_02068388(param0->unk_40, 1);
                        func_02029264((int) param0, (unsigned char *) (a + 0x1c));
                        ok = 1;
                    }
                }
            }
        }
    }
    if (ok == 0) {
        func_0201cfb4(param0, &st);
        func_0201cf74(param0, &st, 0, &data_020c8928, (void *) data_021c1e14);
        func_0201cf74(param0, &st, 1, &data_020c8924, (void *) data_021c1d6c);
        st.a = 2;
        st.b = st.a - 1;
        func_0201cec8(param0, &st);
        func_0202da74(param0, data_020d8de8);
        func_02068388(param0->unk_40, 1);
        ok = 1;
    }
    return ok;
}
