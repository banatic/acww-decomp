/* func_020899a8 @ 0x020899a8, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern struct Node *data_021d3124;

extern void func_0203f844(Vec *, int);
extern void func_020eaca0(Vec *, Vec *, Vec *);
extern s32 FX_Div(s32, s32);
extern s32 FX_MulFunc(s32, s32);
extern long long func_01ffd028(Vec *, struct Node *);

int func_020899a8(int a, int b, s32 c, u8 *d)
{
    int ret;
    s32 t;
    struct Node *node;
    unsigned int i, j;
    Vec va, vb, dv;
    Vec arr[6];

    ret = 0;
    node = data_021d3124;
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
