/* catch_sphere: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02089b04 @ 0x02089b04, 0x1a bytes, Thumb
 * func_02089af4 @ 0x02089af4, 0x10 bytes, Thumb
 * func_02089aa8 @ 0x02089aa8, 0x4c bytes, Thumb
 * func_020899a8 @ 0x020899a8, 0x100 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02089b04 {
    char pad_00[0x1c];
    int unk_1C;
    char unk_20;
} UnkStruct_02089b04;

typedef struct UnkStruct_02089aa8 {
    char pad_00[0x1c];
    struct UnkStruct_02089aa8 *next;
    unsigned char unk_20;
    char pad_21[3];
    int unk_24;
} UnkStruct_02089aa8;

typedef struct Vec {
    s32 x, y, z;
} Vec;

struct Node {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 pad_11[0xb];
    struct Node *next;
    u8 unk_20;
    u8 pad_21[3];
    s32 unk_24;
};

extern void *func_020b7f88(void *self);
extern int func_020b7f50(int);
extern UnkStruct_02089aa8 *data_021d3124;
extern void *func_020b6590(void);
extern void func_020b7d84(void *, UnkStruct_02089aa8 *, int, int, int, unsigned char);
extern int func_0203f844(Vec *, int);
extern void func_020eaca0(Vec *, Vec *, Vec *);
extern s32 FX_Div(s32, s32);
extern s32 FX_MulFunc(s32, s32);
extern long long func_01ffd028(Vec *, struct Node *);

void *func_02089b04(UnkStruct_02089b04 *self)
{
    func_020b7f88(self);
    self->unk_1C = 0;
    self->unk_20 = 0;
    return self;
}

int func_02089af4(int x)
{
    func_020b7f50(x);
    return x;
}

void func_02089aa8(UnkStruct_02089aa8 *self, int a1, int a2, int a3, unsigned char a4)
{
    self->next = 0;
    if (data_021d3124 == 0) {
        data_021d3124 = self;
    } else {
        self->next = data_021d3124;
        data_021d3124 = self;
    }
    self->unk_20 = 0;
    self->unk_24 = a2;
    func_020b7d84(func_020b6590(), self, a1, a3, 4, a4);
}

int func_020899a8(int a, int b, s32 c, u8 *d, int e)
{
    int ret;
    s32 t;
    struct Node *node;
    unsigned int i, j;
    Vec va, vb, dv;
    Vec arr[6];

    ret = 0;
    node = (*(struct Node **) &data_021d3124);
    func_0203f844(&va, a);
    func_0203f844(&vb, b);
    func_020eaca0(&dv, &vb, &va);
    dv.x = FX_Div(dv.x, 0x6000);
    dv.y = FX_Div(dv.y, 0x6000);
    dv.z = FX_Div(dv.z, 0x6000);
    for (i = 0; i < 6; i++) {
        arr[i].x = va.x + i * dv.x;
        arr[i].y = va.y + i * dv.y;
        arr[i].z = va.z + i * dv.z;
    }
    while (node) {
        node->unk_20 = 0;
        t = FX_MulFunc(c + node->unk_24, c + node->unk_24);
        for (j = 0; j < 6; j++) {
            if ((long long) t >= func_01ffd028(&arr[j], node)) {
                node->unk_20 = 1;
                ret = 1;
                if (d) {
                    *d = node->unk_10;
                }
                break;
            }
        }
        node = node->next;
    }
    return ret;
}
