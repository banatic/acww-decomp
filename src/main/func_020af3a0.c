/* func_020af3a0 @ 0x020af3a0, 0x2a8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020af3a0 {
    u16 unk_00;
    u16 unk_02;
    int a;
    int b;
} UnkStruct_020af3a0;

typedef struct UnkStruct_020af3a0_3 {
    char pad_00[4];
    u16 arr[0x25];
    char pad_4E[0x5a - 0x4e];
    u16 f5a : 5;
    u16 f5arest : 11;
} UnkStruct_020af3a0_3;

typedef struct UnkStruct_020af3a0_2 {
    int unk_00;
    int w1;
} UnkStruct_020af3a0_2;

extern void func_020ae9c0(void *);
extern int func_020ad798(void);
extern void func_020ad78c(int);
extern void func_020b5e70(void);
extern int func_020b6744(void);
extern int func_020b65c4(void);
extern void func_0209e474(int *);
extern void func_0209e140(int *, int);
extern int func_020af2d0(UnkStruct_020af3a0_3 *, int *);
extern int func_02073d90(int);
extern void func_020ade78(void);
extern void func_020af298(UnkStruct_020af3a0_3 *, int *);
extern void func_020af31c(UnkStruct_020af3a0_3 *, int, int, int);
extern int func_02098880(void *);
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_02098844(void *, int);
extern int func_02099a28(int);
extern u8 *func_020afad4(UnkStruct_020af3a0_3 *);
extern void func_020af03c(UnkStruct_020af3a0_3 *, int *);
extern int func_02063cd4(void *, int);
extern void func_020afd58(u8);
extern int func_020afb48(UnkStruct_020af3a0_3 *, int *);
extern void func_02063ccc(void *, int, int);
extern void func_02063cc8(void *);
extern void __register_global_object(void *, void *, void *);
extern int func_0204bcdc(u16 *);
extern void func_020638d4(u16 *, void *, int, void *, int, int, int);
extern void func_020afd24(u16 *);

extern char data_021f3b44[];
extern int data_020ccf94;
extern char data_021dc7bc[];
extern char data_021f4a80[];
extern int data_021f4a08;
extern UnkStruct_020af3a0_2 data_021f4a0c;
extern char data_021f4a98[];

void func_020af3a0(UnkStruct_020af3a0_3 *self, int arg1)
{
    UnkStruct_020af3a0 s;
    UnkStruct_020af3a0_2 o[3];
    int g;
    int p;
    int x;
    unsigned int v;
    unsigned int i;
    int j;
    int r6;
    int r7;
    int code;
    u16 *q;

    func_020ae9c0(data_021f3b44);
    if (func_020ad798() == 1) {
        func_020ad78c(2);
        return;
    }
    func_020b5e70();
    if (func_020b6744() == 0) {
        v = func_020b65c4();
        if (v == 0x2c) {
            return;
        }
        if (v == 0x3f) {
            return;
        }
    }
    r6 = 1;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s.a);
    if (((u8 *) &s)[6] < 6) {
        func_0209e140(&s.a, r6);
        r6 = 0;
    }
    if (arg1 == 0) {
        if (func_020af2d0(self, &s.a) == 0) {
            return;
        }
    }
    self->f5a = 0;
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    func_020ade78();
    func_020af298(self, &s.a);
    func_020af31c(self, ((u8 *) &s)[9], ((u8 *) &s)[8], ((u8 *) &s)[7]);

    r7 = 1;
    x = func_02098880(data_021dc7bc);
    if (x != 0) {
        if (x == 1) {
            g = func_020984e8();
            if (g == 0 || func_02099020(g, r7) == 0) {
                r7 = 0;
            }
        } else {
            for (j = 0; j < 4; j++) {
                p = func_02098844(data_021dc7bc, j);
                if (p == 0) {
                    continue;
                }
                if (func_02099a28(p) == 0) {
                    continue;
                }
                if (func_02099020(p, 1) != 0) {
                    continue;
                }
                r7 = 0;
                break;
            }
        }
    }

    if (r7 == 0) {
        if (func_020afad4(self)[3] == 0) {
            func_020af03c(self, &s.a);
            if (func_02063cd4(data_021f4a80, 0xe) == 0) {
                v = func_02063cd4(data_021f4a80, 4);
                self->f5a = (u8) (v + 0x11);
                if (r6 != 0) {
                    func_020afd58((u8) self->f5a);
                }
            }
            if (self->f5a == 0) {
                if (func_020afb48(self, &s.a) == 0) {
                    if ((data_021f4a08 & 1) == 0) {
                        func_02063ccc(&data_021f4a0c, 0, 4);
                        __register_global_object(&data_021f4a0c, (void *) func_02063cc8, data_021f4a98);
                        data_021f4a08 |= 1;
                    }
                    if (func_02063cd4(data_021f4a80, 5) == 0) {
                        for (i = 0; i < 0x25; i++) {
                            u16 *e = &self->arr[i];
                            if (func_0204bcdc(e) != 0) {
                                o[1].unk_00 = data_021f4a0c.unk_00;
                                o[1].w1 = data_021f4a0c.w1;
                                func_020638d4(&s.unk_00, &o[1], 0, data_021f4a80, 0, 1, 0);
                                *e = s.unk_00;
                                func_02063cc8(&o[1]);
                                if (r6 != 0) {
                                    func_020afd24(e);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if (((u8 *) &s)[8] != 0xc) {
        return;
    }
    v = ((u8 *) &s)[7];
    code = 0x2e;
    if (v >= 0xa && v <= 0x18) {
        code = 0x2b;
    } else if (v >= 0x1a && v <= 0x1f) {
        code = 0x2c;
    }
    if (code == 0x2e) {
        return;
    }
    r7 = 0;
    for (i = 0; i < 0x25; i++) {
        if (func_0204bcdc(&self->arr[i]) != 0) {
            if (r7 == 1) {
                func_02063ccc(&o[0], 0, code);
                o[2].unk_00 = o[0].unk_00;
                o[2].w1 = o[0].w1;
                func_020638d4(&s.unk_02, &o[2], 0, data_021f4a80, 0, 1, 0);
                self->arr[i] = s.unk_02;
                func_02063cc8(&o[2]);
                func_02063cc8(&o[0]);
                break;
            }
            r7++;
        }
    }
}
