/* The copy of overlay 69's tables of line members into main (villager_line_tables.h). */
#include "villager_line_tables.h"

#include <string.h>

#include "clean.h"

/* Main's tables, each where its users read it. */
extern MemberPointer data_021c1d54[], data_021c1d6c[], data_021c1e14[], data_021c1f04[], data_021c1fe4[], data_021c2044[],
    data_021c219c[], data_021c222c[], data_021c22d4[], data_021c2394[], data_021c2454[], data_021c252c[], data_021c2704[],
    data_021c283c[], data_021c29d4[];
/* The overlay's tables, as its static initialiser fills them. */
extern const MemberPointer data_ov069_02268304[], data_ov069_0226831c[], data_ov069_02268334[], data_ov069_02268364[],
    data_ov069_022683ac[], data_ov069_0226840c[], data_ov069_0226846c[], data_ov069_022684fc[], data_ov069_022685a4[],
    data_ov069_02268664[], data_ov069_02268724[], data_ov069_022687fc[], data_ov069_022688d4[], data_ov069_02268a0c[],
    data_ov069_02268ba4[];

/* A table copied: where to, from where, how many entries. */
typedef struct VillagerLineCopy {
    MemberPointer *to;
    const MemberPointer *from;
    u32 entries;
} VillagerLineCopy;

/* func_ov069_022667e0: the fifteen tables copied into main's, in this order (memcpy). The
 * arguments are not used. */
void VillagerLineTables_Copy(int unused_a, int unused_b)
{
    (void) unused_a;
    (void) unused_b;
    static const VillagerLineCopy copies[VILLAGER_LINE_TABLES] = {
        {data_021c1f04, data_ov069_02268364, 9},   {data_021c283c, data_ov069_02268a0c, 51},
        {data_021c2704, data_ov069_022688d4, 39},  {data_021c1d54, data_ov069_02268304, 3},
        {data_021c1d6c, data_ov069_0226831c, 3},   {data_021c1e14, data_ov069_02268334, 6},
        {data_021c29d4, data_ov069_02268ba4, 219}, {data_021c219c, data_ov069_0226846c, 18},
        {data_021c2454, data_ov069_022687fc, 27},  {data_021c22d4, data_ov069_02268664, 24},
        {data_021c1fe4, data_ov069_022683ac, 12},  {data_021c252c, data_ov069_02268724, 27},
        {data_021c2044, data_ov069_0226840c, 12},  {data_021c2394, data_ov069_022685a4, 24},
        {data_021c222c, data_ov069_022684fc, 21},
    };
    for (int i = 0; i < VILLAGER_LINE_TABLES; i++) {
        memcpy(copies[i].to, copies[i].from, copies[i].entries * sizeof(MemberPointer));
    }
}
CLEAN_AS(func_ov069_022667e0, VillagerLineTables_Copy)
