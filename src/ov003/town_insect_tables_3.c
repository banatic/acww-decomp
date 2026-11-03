/* town_insect_tables_3: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02235c94 @ 0x02235c94, 0x54 bytes, Thumb
 * func_ov003_02235c34 @ 0x02235c34, 0x60 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
} UnkStruct_02235c94;

typedef struct UnkStruct_02235c34 UnkStruct_02235c34;

typedef struct UnkStruct_02235c34_2 UnkStruct_02235c34_2;

extern UnkStruct_02235c94 data_ov003_02262aa8[];
extern void func_020779b8(void *buf, int a, int b);
extern int func_0207762c(int id);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern int func_020a7278(void);
extern int func_02073d90(UnkStruct_02235c34_2 *g);
extern UnkStruct_02235c34 *func_020738bc(UnkStruct_02235c34_2 *g, void *k);
extern void func_02077978(UnkStruct_02235c34 *e, int a, int *b);
extern UnkStruct_02235c34_2 *data_020ccf94;

void func_ov003_02235c94(void *dst, int id, void *context)
{
    u8 buf[8];
    int i;

    i = id - 0x18;
    func_020779b8(buf, data_ov003_02262aa8[i].unk_00, data_ov003_02262aa8[i].unk_08);
    buf[5] = data_ov003_02262aa8[i].unk_0C;
    buf[6] = data_ov003_02262aa8[i].unk_0D;
    MI_CpuCopy8(buf, dst, func_0207762c(id));
}

int func_ov003_02235c34(void *a1, u8 *a2, s8 *a3, int a4, int *a5, u8 *a6)
{
    UnkStruct_02235c34_2 *g;
    UnkStruct_02235c34 *e;

    if (func_020a7278() == 0) {
        g = data_020ccf94;
        if (func_02073d90(g) != 0) {
            e = func_020738bc(g, a2 + 0x18);
            if (e != 0) {
                func_02077978(e, a4, a5);
                if (*a5 > 0) {
                    *a3 = *(s8 *) ((u8 *) e + 5);
                    *a6 = *((u8 *) e + 6);
                    return 1;
                }
            }
        }
    }
    return 0;
}
