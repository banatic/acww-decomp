/* scene_motion: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02016bfc @ 0x02016bfc, 0x170 bytes, Thumb
 * func_02016a48 @ 0x02016a48, 0x1b4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    u8 pad_04[0x94];
    u8 unk_98;
} UnkStruct_02016bfc;

typedef struct {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad_60[0x04];
    int unk_64;
    u8 pad_68[0x26];
    short unk_8E;
    u8 pad_90[0x2c0];
    u8 sub[1];
} UnkStruct_02016bfc_2;

struct Work {
    unsigned char pad_00[0x5c];
    int unk_5C;
    unsigned char pad1[0x64 - 0x60];
    int unk_64;
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;
    unsigned char pad_90[0x94 - 0x90];
    short unk_94;
};

struct UnkStruct_02016a48 {
    int unk_00;
    unsigned char pad1[0x98 - 4];
    unsigned char unk_98;
};

extern int func_0201bee0(UnkStruct_02016bfc_2 *s, int *vec, short *h);
extern int FX_MulFunc(int a, int b);
extern int func_020e8ed8(int x, int y);
extern int func_0201c3dc(int v);
extern int func_0201afec(void *sub);
extern void func_0201aff4(void *sub, int v);
extern void func_0201b1a4(void *sub, UnkStruct_02016bfc_2 *s, int a, int b, int data);
extern void func_0201b044(void *sub, void *ptr);
extern void func_0201afd4(void *sub, void *ptr);
extern unsigned short data_020c80f8;
extern void func_0201b188(void *, void *);
extern char data_021fbee8[];

void func_02016bfc(UnkStruct_02016bfc *s0, UnkStruct_02016bfc_2 *s1)
{
    int sum;
    short h[1];
    int vec[3];
    int dx, dy;
    int angle;

    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
    h[0] = s1->unk_8E;

    if (func_0201bee0(s1, vec, h) != 0) {
        dx = vec[0] - s1->unk_5C;
        dy = vec[2] - s1->unk_64;
        sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);

        if (sum < 0x29) {
            if (h[0] != func_0201afec(&s1->sub)) {
                func_0201aff4(&s1->sub, h[0]);
                return;
            } else {
                int res = func_0201afec(&s1->sub);
                if (res == s1->unk_8E) {
                    s0->unk_98 = 0;
                }
                return;
            }
        } else {
            angle = func_020e8ed8(dx, dy);
            if (func_0201c3dc((short) (angle - h[0]))) {
                if (s0->unk_00 == 2) {
                    func_0201b1a4(&s1->sub, s1, 2, 0, data_020c80f8);
                } else {
                    func_0201b1a4(&s1->sub, s1, 1, 0, data_020c80f8);
                }
                func_0201aff4(&s1->sub, h[0]);
                s0->unk_98 = 1;
            } else {
                func_0201b1a4(&s1->sub, s1, 4, 0, data_020c80f8);
                func_0201aff4(&s1->sub, angle);
                s0->unk_98 = 3;
            }
            func_0201b044(&s1->sub, &vec[0]);
            func_0201afd4(&s1->sub, &vec[0]);
        }
    } else {
        func_0201b1a4(&s1->sub, s1, 0, 0, data_020c80f8);
        func_0201aff4(&s1->sub, h[0]);
        func_0201b044(&s1->sub, ((int *) data_021fbee8));
        func_0201afd4(&s1->sub, ((int *) data_021fbee8));
        s0->unk_98 = 0;
    }
}

void func_02016a48(struct UnkStruct_02016a48 *self, struct Work *work)
{
    int coord[3];
    short angle;
    int dx, dy;
    int sum;
    int v;

    coord[0] = 0;
    coord[1] = 0;
    coord[2] = 0;
    angle = work->unk_8E;

    func_0201b188((char *) work + 0x350, work);

    if (func_0201bee0((UnkStruct_02016bfc_2 *) work, coord, &angle) != 0) {
        dx = coord[0] - work->unk_5C;
        dy = coord[2] - work->unk_64;
        sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);

        if (sum == 0) {
            work->unk_94 = work->unk_8E;
            if (angle != work->unk_8E) {
                func_0201b1a4((char *) work + 0x350, (UnkStruct_02016bfc_2 *) work, 3, 0, data_020c80f8);
                func_0201aff4((char *) work + 0x350, angle);
                self->unk_98 = 2;
            } else {
                func_0201b1a4((char *) work + 0x350, (UnkStruct_02016bfc_2 *) work, 0, 0, data_020c80f8);
                func_0201aff4((char *) work + 0x350, angle);
                func_0201b044((char *) work + 0x350, data_021fbee8);
                func_0201afd4((char *) work + 0x350, data_021fbee8);
                self->unk_98 = 0;
            }
        } else {
            if (sum >= 0x29) {
                v = func_020e8ed8(dx, dy);
                if (func_0201c3dc((short) (v - angle)) != 0) {
                    if (self->unk_00 == 2) {
                        func_0201b1a4((char *) work + 0x350, (UnkStruct_02016bfc_2 *) work, 2, 0, data_020c80f8);
                    } else {
                        func_0201b1a4((char *) work + 0x350, (UnkStruct_02016bfc_2 *) work, 1, 0, data_020c80f8);
                    }
                    work->unk_94 = work->unk_8E;
                    func_0201aff4((char *) work + 0x350, angle);
                    self->unk_98 = 1;
                } else {
                    func_0201aff4((char *) work + 0x350, v);
                }
                func_0201b044((char *) work + 0x350, coord);
                func_0201afd4((char *) work + 0x350, coord);
            }
        }
    } else {
        func_0201b1a4((char *) work + 0x350, (UnkStruct_02016bfc_2 *) work, 0, 0, data_020c80f8);
        func_0201aff4((char *) work + 0x350, angle);
        func_0201b044((char *) work + 0x350, data_021fbee8);
        func_0201afd4((char *) work + 0x350, data_021fbee8);
        self->unk_98 = 0;
    }
}
