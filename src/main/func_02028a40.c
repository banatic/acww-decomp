/* func_02028a40 @ 0x02028a40, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02028a40 {
    int x;
    int y;
};

struct ST {
    int pad_00[8];
    u8 a;
    u8 b;
    u8 pad_22[2];
};

struct UnkStruct_02028a40_2 {
    char pad_00[0x40];
    int unk_40;
};

extern void *data_021e5a2c;
extern int data_020c8928;
extern int data_020c8924;
extern struct UnkStruct_02028a40 data_020d8e78;

extern int func_0207b3dc(void *a);
extern int func_0207f294(int a);
extern unsigned int func_0207b410(unsigned int address);
extern void *func_0209a778(void *record);
extern int func_0209bd44(void *);
extern int func_0209a610(void *a, int b);
extern void *func_0209a4b8(void *a);
extern int func_020951bc(void *);
extern int func_020984e8(void);
extern void *func_02099870(int);
extern void func_0201cfb4(struct UnkStruct_02028a40_2 *a, struct ST *st);
extern int memcmp(const void *a, const void *b, u32 n);
extern int func_0209518c(void *a, void *b);
extern int func_0209bba0(void *a);
extern int func_0209a69c(void *a, void *b);
extern void func_0201cf74(struct UnkStruct_02028a40_2 *a, struct ST *st, int idx, void *data, void *str);
extern void func_0201cec8(struct UnkStruct_02028a40_2 *a, struct ST *st);
extern void func_0202da74(struct UnkStruct_02028a40_2 *a, struct UnkStruct_02028a40 p);
extern void func_02068388(int a, int b);
extern void func_02015e40(struct UnkStruct_02028a40_2 *a, void *b, int c);

extern unsigned char data_021c1d6c[];
extern unsigned char data_021c2f2c[];
extern unsigned char data_021c2f44[];
extern unsigned char data_021c2f5c[];
extern unsigned char data_021c2fbc[];

int func_02028a40(struct UnkStruct_02028a40_2 *param0, int param1)
{
    void *r7;
    int res;
    void *local1;
    void *p_a4b8;
    void *p_9870;
    struct ST st;
    void *str_ptr;

    r7 = &data_021e5a2c;
    res = func_0207b3dc(r7);
    if (res == ~0) {
        goto fail;
    }
    if (res != func_0207f294(param1)) {
        goto fail;
    }

    r7 = (void *) func_0207b410((unsigned int) r7);
    local1 = func_0209a778(r7);
    if (func_0209bd44(local1) == 0) {
        goto fail;
    }
    if (func_0209a610(r7, 0) == 0) {
        goto fail;
    }
    p_a4b8 = func_0209a4b8(r7);
    if (p_a4b8 == 0) {
        goto fail;
    }
    if (func_020951bc(p_a4b8) == 0) {
        goto fail;
    }

    p_9870 = func_02099870((int) func_020984e8());

    func_0201cfb4(param0, &st);

    if (*(u16 *) p_9870 == *(u16 *) p_a4b8 && memcmp((char *) p_9870 + 2, (char *) p_a4b8 + 2, 12) == 0 &&
        func_0209518c(p_9870, p_a4b8) != 0) {
        if (func_0209bba0(local1) == 1) {
            str_ptr = (void *) data_021c2fbc;
        } else {
            str_ptr = (void *) data_021c2f5c;
        }
    } else {
        if (func_0209a69c(r7, p_9870) != 0) {
            str_ptr = (void *) data_021c2f44;
        } else {
            str_ptr = (void *) data_021c2f2c;
        }
    }

    func_0201cf74(param0, &st, 0, &data_020c8928, str_ptr);
    func_0201cf74(param0, &st, 1, &data_020c8924, (void *) data_021c1d6c);

    st.a = 2;
    st.b = st.a - 1;

    func_0201cec8(param0, &st);
    func_0202da74(param0, data_020d8e78);
    func_02068388(param0->unk_40, 1);
    func_02015e40(param0, p_a4b8, 1);

    return 1;

fail:
    return 0;
}
