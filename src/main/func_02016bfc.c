/* func_02016bfc @ 0x02016bfc, 0x170 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
extern int data_021fbee8;

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
        func_0201b044(&s1->sub, &data_021fbee8);
        func_0201afd4(&s1->sub, &data_021fbee8);
        s0->unk_98 = 0;
    }
}
