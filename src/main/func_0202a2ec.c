/* func_0202a2ec @ 0x0202a2ec, 0x1ec bytes, Thumb, module main
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
    signed char b;
    u8 pad_22[2];
};

struct UnkStruct_0202a2ec {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x11c];
    int unk_160;
};

extern int data_020c8920;
extern int data_020c8924;
extern int data_020c8928;
extern int data_020c8930;
extern struct Pair data_020d8f20;

extern int func_0208150c(int a);
extern int func_0209ad2c(int a, int b, int c);
extern int func_0209b4d4(int a);
extern int func_0209bba8(int a);
extern int func_0209b414(int a);
extern int func_020984e8(void);
extern void func_0209e474(void *p);
extern void func_0201cfb4(struct UnkStruct_0202a2ec *a, struct ST *st);
extern void func_0202d9d0(struct UnkStruct_0202a2ec *a, int b);
extern int func_0209b4cc(int a, int b);
extern void func_02015e10(struct UnkStruct_0202a2ec *a, int b, int c);
extern void *func_0202d9c4(struct UnkStruct_0202a2ec *a);
extern int func_0209bb70(int a);
extern void func_02015de4(struct UnkStruct_0202a2ec *a, int b, int c, int d);
extern int func_0209bc20(void *a);
extern int func_0209e3ac(int a, void *b, int c);
extern int func_02099734(int a);
extern int func_0202d794(int a, int b);
extern void func_0201cf90(struct UnkStruct_0202a2ec *a, struct ST *st, int idx, int w, int h, void *str);
extern void func_0201cf74(struct UnkStruct_0202a2ec *a, struct ST *st, int idx, void *data, void *str);
extern void func_0201cec8(struct UnkStruct_0202a2ec *a, struct ST *st);
extern void func_0202da74(struct UnkStruct_0202a2ec *a, struct Pair p);
extern void func_02068388(int a, int b);

extern unsigned char data_021c1d6c[];
extern unsigned char data_021c1e14[];
extern unsigned char data_021c2ac4[];
extern unsigned char data_021c2b0c[];

int func_0202a2ec(struct UnkStruct_0202a2ec *self, int param1, int param2)
{
    int a;
    int b;
    int mode;
    int ret;
    u8 idx;
    int p10;
    int t;
    u8 n;
    int buf[2];
    struct ST st;

    a = func_0209ad2c(param2, func_0208150c(param1), 1);
    if (a != 0) {
        b = func_0209b4d4(a);
    } else {
        b = 0;
    }
    if (b != 0) {
        mode = func_0209bba8(b);
    } else {
        mode = 4;
    }
    ret = 0;
    switch (mode) {
        case 0:
        case 2:
            if (func_0209b414(a) != 0) {
                break;
            }
            idx = 0;
            buf[0] = idx;
            buf[1] = idx;
            p10 = func_020984e8();
            func_0209e474(buf);
            func_0201cfb4(self, &st);
            self->unk_160 = a;
            func_0202d9d0(self, b);
            func_02015e10(self, func_0209b4cc(self->unk_160, idx), idx);
            func_02015e10(self, func_0209b4cc(self->unk_160, 1), 1);
            func_02015de4(self, func_0209bb70((int) func_0202d9c4(self)), idx, 7);
            if (func_0209e3ac(func_0209bc20(func_0202d9c4(self)), buf, 0x3f) == -1) {
                switch (mode) {
                    case 2:
                        func_0201cf90(self, &st, idx, 0x2b, 0x2b, (void *) data_021c2ac4);
                        idx++;
                        ret = 1;
                        break;
                    case 0:
                        func_0201cf90(self, &st, idx, 0x27, 0x27, (void *) data_021c2ac4);
                        idx++;
                        ret = 1;
                        break;
                }
            } else {
                switch (mode) {
                    case 2:
                        func_0201cf74(self, &st, idx, &data_020c8920, (void *) data_021c2b0c);
                        idx++;
                        ret = 1;
                        break;
                    case 0:
                        t = func_02099734(p10);
                        if (func_0202d794(t, func_0209bb70(func_0209b4d4(self->unk_160))) != -1) {
                            func_0201cf74(self, &st, idx, &data_020c8930, (void *) data_021c2b0c);
                            idx++;
                            ret = 1;
                        }
                        break;
                }
            }
            if (ret != 0) {
                func_0201cf74(self, &st, idx, &data_020c8928, (void *) data_021c1e14);
                func_0201cf74(self, &st, (u8) (idx + 1), &data_020c8924, (void *) data_021c1d6c);
                n = idx + 2;
                st.a = n;
                st.b = n - 1;
                func_0201cec8(self, &st);
                func_0202da74(self, data_020d8f20);
                func_02068388(self->unk_40, 1);
            }
            break;
    }
    return ret;
}
