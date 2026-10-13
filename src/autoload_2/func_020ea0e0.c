/* func_020ea0e0 @ 0x020ea0e0, 0xdc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void *data_021fbe94;
extern u16 data_0213e5a4;

extern int func_020e9d64(void *heap, int align);
extern void *func_020e9ed4(void *heap, u32 size, int align);
extern void func_020e9c48(void *heap, void *block);
extern int NNS_FndCreateFrmHeapEx(void *p, int n, u16 c);
extern void *func_020ea3f0(void *obj, void *p, int n, void *heap, int ret);

void *func_020ea0e0(int size, void *heap)
{
    u32 allocSize;
    int total;
    void *block;
    void *p;
    int ret;

    if (heap == 0) {
        heap = data_021fbe94;
    }
    if (size == -1) {
        allocSize = (u32) func_020e9d64(heap, 4);
        if (allocSize < 0x48) {
            return 0;
        }
        total = (int) (allocSize - 0x18);
    } else {
        total = ((size + 3) & ~3) + 0x30;
        allocSize = (u32) (total + 0x18);
    }
    block = func_020e9ed4(heap, allocSize, 4);
    if (block != 0) {
        p = (char *) block + 0x18;
        ret = NNS_FndCreateFrmHeapEx(p, total, data_0213e5a4);
        if (ret == 0) {
            func_020e9c48(heap, block);
            block = 0;
        } else if (block != 0) {
            func_020ea3f0(block, p, total, heap, ret);
        }
    }
    return block;
}
