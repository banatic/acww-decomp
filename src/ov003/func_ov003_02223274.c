/* func_ov003_02223274 @ 0x02223274, 0x30c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Node {
    u8 pad_00[0xd];
    u8 unk_0D;
} Node;

typedef struct UnkStruct_02223274_4 {
    int unk_00;
    int unk_04;
    int unk_08;
    u8 pad_0C[0x64 - 0x0c];
    void *unk_64;
    u8 pad_68[0xa4 - 0x68];
    int unk_A4;
    u8 pad_A8[4];
    unsigned int ac_lo : 12;
    unsigned int ac_val : 16;
    unsigned int ac_hi : 4;
    u8 pad_B0[8];
    u8 unk_B8;
    u8 pad_B9[7];
    int unk_C0;
    int unk_C4;
    int unk_C8;
    int unk_CC;
    int unk_D0;
    u32 unk_D4;
    int unk_D8;
    int unk_DC;
    int unk_E0;
    u8 pad_E4[0x144 - 0xe4];
    Node *unk_144;
    Node *unk_148;
} UnkStruct_02223274_4;

typedef struct UnkStruct_02223274 {
    int x;
    int y;
} UnkStruct_02223274;

typedef struct UnkStruct_02223274_2 {
    int x;
    int y;
    int z;
} UnkStruct_02223274_2;

typedef struct UnkStruct_02223274_3 {
    u8 pad_00[0x68];
    int unk_68;
} UnkStruct_02223274_3;

extern UnkStruct_02223274_3 *data_020ccf94;
extern int data_ov003_0223cfa0;

extern void func_02055124(int *);
extern int func_02056f94(int *);
extern void func_ov003_02222c68(UnkStruct_02223274_4 *);
extern void func_020044c0(int *, int, int, int);
extern void func_020044d0(int *, UnkStruct_02223274_2 *);
extern void func_0210744c(void *, int);
extern void func_02107494(void *, int);
extern void *func_0204e414(void);
extern u16 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204b5ac(u16 *);
extern int func_0204b7a0(u16 *);
extern Node *func_ov003_02223c7c(void *, u32, int, u16 *, UnkStruct_02223274 *, int);
extern Node *func_ov003_02223d14(void *, u32, int, u16 *, UnkStruct_02223274 *, int);

void func_ov003_02223274(UnkStruct_02223274_4 *self)
{
    UnkStruct_02223274 a;
    UnkStruct_02223274 b;
    UnkStruct_02223274_2 c;
    int flag;
    int base;
    void *h;
    u16 *it;
    int n;
    int q0;
    int q1;
    int s0;
    int s1;

    if (self->unk_00 == 1) {
        func_02055124(&self->unk_08);
        if (func_02056f94(&self->unk_A4) != 0) {
            func_ov003_02222c68(self);
        } else {
            flag = 0;
            base = data_020ccf94->unk_68;
            switch (self->unk_D4) {
                case 4:
                case 5:
                    if (self->ac_val >= 0x11) {
                        self->unk_D8 -= 0x2955;
                        if (self->unk_D8 < 0) {
                            self->unk_D8 = 0;
                        }
                    }
                    switch (self->unk_DC) {
                        case 0:
                            if (self->ac_val >= 4) {
                                flag = 1;
                            }
                            break;
                        case 1:
                            if (self->ac_val >= 0x14) {
                                flag = 1;
                                func_020044c0(&self->unk_E0, 0x7ea, 0x7f, 0);
                            }
                            break;
                    }
                    break;
                case 6:
                case 7:
                    if (self->ac_val >= 0x11) {
                        self->unk_D8 -= 0x2627;
                        if (self->unk_D8 < 0) {
                            self->unk_D8 = 0;
                        }
                    }
                    switch (self->unk_DC) {
                        case 0:
                            if (self->ac_val >= 4) {
                                flag = 1;
                            }
                            break;
                        case 1:
                            if (self->ac_val >= 0xd) {
                                flag = 1;
                                func_020044c0(&self->unk_E0, 0x7ea, 0x7f, 0);
                            }
                            break;
                    }
                    break;
                case 2:
                    if (self->unk_DC == 0 && self->ac_val >= 4) {
                        flag = 1;
                    } else {
                        if (self->unk_144 != 0) {
                            self->unk_144->unk_0D = 0x1a;
                        }
                        if (self->unk_148 != 0) {
                            self->unk_148->unk_0D = 0x1a;
                        }
                    }
                    break;
                case 0:
                    if (self->unk_DC == 0 && self->ac_val >= 4) {
                        flag = 1;
                    }
                    break;
                case 1:
                default:
                    if (self->unk_DC == 0 && self->ac_val >= 4) {
                        flag = 1;
                    }
                    break;
                case 3:
                    break;
            }

            func_0210744c(self->unk_64, self->unk_D8 >> 12);
            base += 0x33;
            func_02107494(self->unk_64, base);

            if (flag != 0) {
                h = func_0204e414();
                if (h != 0) {
                    q0 = self->unk_CC;
                    q1 = self->unk_D0;
                    s0 = q0 >> 4;
                    s1 = q1 >> 4;
                    it = func_0204f5e0(h, s0, s1, q0 - (s0 << 4), q1 - (s1 << 4), 0);
                    if (it != 0) {
                        int t3 = 1;
                        int t2 = 1;
                        int t1 = 1;
                        int t0 = 0;
                        unsigned int k;
                        k = *it;
                        if (k >= 0x2b && k <= 0x2e) {
                            t0 = 1;
                        }
                        if (t0 == 0 && !(k >= 0xff && k <= 0x102)) {
                            t1 = 0;
                        }
                        if (t1 == 0 && !(k >= 0x62 && k <= 0x65)) {
                            t2 = 0;
                        }
                        if (t2 == 0 && !(k >= 0xd0 && k <= 0xd3)) {
                            t3 = 0;
                        }
                        if (t3) {
                            n = func_0204b5ac(it);
                        } else {
                            n = func_0204b7a0(it);
                        }
                        if (n > 0) {
                            a.x = self->unk_CC;
                            a.y = self->unk_D0;
                            self->unk_144 =
                                func_ov003_02223c7c(&data_ov003_0223cfa0, self->unk_D4, n - 1, it, &a, self->unk_DC);
                            b.x = self->unk_CC;
                            b.y = self->unk_D0;
                            self->unk_148 =
                                func_ov003_02223d14(&data_ov003_0223cfa0, self->unk_D4, n - 1, it, &b, self->unk_DC);
                            self->unk_DC++;
                        }
                    }
                }
            }
        }
        c.x = self->unk_C0;
        c.y = self->unk_C4;
        c.z = self->unk_C8;
        func_020044d0(&self->unk_E0, &c);
    }
    self->unk_B8 = 1;
}
