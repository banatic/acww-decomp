/* func_ov003_02235c34 @ 0x02235c34, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02235c34 UnkStruct_02235c34;
typedef struct UnkStruct_02235c34_2 UnkStruct_02235c34_2;

extern int func_020a7278(void);
extern int func_02073d90(UnkStruct_02235c34_2 *g);
extern UnkStruct_02235c34 *func_020738bc(UnkStruct_02235c34_2 *g, void *k);
extern void func_02077978(UnkStruct_02235c34 *e, int a, int *b);

extern UnkStruct_02235c34_2 *data_020ccf94;

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
