/* func_02029ca4 @ 0x02029ca4, 0x174 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

struct UnkStruct_02029ca4 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x120];
    int unk_164;
};

typedef struct {
    u16 bits;
    u8 count;
} FlagStruct;

extern int data_020c8924;
extern int data_020c8928;
extern struct Pair data_020d8e98;

extern void *func_0202d9c4(struct UnkStruct_02029ca4 *a);
extern int func_0209bba0(void *a);
extern void *func_0209b908(int a);
extern void func_020984e8(void);
extern void *func_02099870(void);
extern int memcmp(const void *a, const void *b, unsigned int n);
extern int func_0209518c(void *a, void *b);
extern int func_02099f1c(FlagStruct *f, int (*cb)(u16 *));
extern int func_02029ebc(u16 *p);
extern int func_020644cc(int a);
extern void func_0201cfb4(struct UnkStruct_02029ca4 *a, struct ST *st);
extern void func_0201cf90(struct UnkStruct_02029ca4 *a, struct ST *st, int idx, int w, int h, void *str);
extern void func_0201cf74(struct UnkStruct_02029ca4 *a, struct ST *st, int idx, void *data, void *str);
extern void func_0201cec8(struct UnkStruct_02029ca4 *a, struct ST *st);
extern void func_0202da74(struct UnkStruct_02029ca4 *a, struct Pair p);
extern void func_02068388(int a, int b);

extern unsigned char data_021c1d6c[];
extern unsigned char data_021c1e14[];
extern unsigned char data_021c2cd4[];
extern unsigned char data_021c2df4[];
extern unsigned char data_021c2eb4[];
extern unsigned char data_021c2ecc[];

int func_02029ca4(struct UnkStruct_02029ca4 *self)
{
    void *p8;
    void *pc;
    FlagStruct flags;
    struct ST st;
    u8 idx;
    u8 n;
    int ret;
    int flag;

    flag = 1;
    idx = 0;
    ret = 0;
    func_0201cfb4(self, &st);
    switch (func_0209bba0(func_0202d9c4(self))) {
        case 0:
            p8 = func_0209b908(self->unk_164);
            func_020984e8();
            pc = func_02099870();
            if (*(u16 *) pc != *(u16 *) p8) {
                break;
            }
            if (memcmp((char *) pc + 2, (char *) p8 + 2, 0xc) != 0) {
                break;
            }
            if (func_0209518c(pc, p8) == 0) {
                break;
            }
            if (func_02099f1c(&flags, func_02029ebc) > 0) {
                func_0201cf90(self, &st, idx, 0x1c, 0x1c, (void *) data_021c2df4);
            } else {
                func_0201cf90(self, &st, idx, 0x14, 0x14, (void *) data_021c2cd4);
            }
            idx++;
            ret = 1;
            break;
        case 1:
            if ((func_020644cc(10) & flag) != 0) {
                func_0201cf74(self, &st, idx, &data_020c8928, (void *) data_021c2eb4);
                flag = 0;
                idx++;
            }
            ret = 1;
            break;
        case 2:
            func_0201cf74(self, &st, idx, &data_020c8928, (void *) data_021c2ecc);
            idx++;
            flag = 0;
            ret = 1;
            break;
    }
    if (ret == 1) {
        if (flag != 0) {
            func_0201cf74(self, &st, idx, &data_020c8928, (void *) data_021c1e14);
            idx++;
        }
        func_0201cf74(self, &st, idx, &data_020c8924, (void *) data_021c1d6c);
        n = idx + 1;
        st.a = n;
        st.b = n - 1;
        func_0201cec8(self, &st);
        func_0202da74(self, data_020d8e98);
        func_02068388(self->unk_40, 1);
    }
    return ret;
}
