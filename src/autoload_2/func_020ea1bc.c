/* func_020ea1bc @ 0x020ea1bc, 0xdc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void *data_021fbe94;
extern u16 data_0213e5a4;

extern int func_020e9d64(void *heap, int align);
extern void *func_020e9ed4(void *heap, u32 size, int align);
extern void func_020e9c48(void *heap, void *block);
extern int NNS_FndCreateExpHeapEx(void *p, int n, u16 c);
extern void *func_020ea41c(void *obj, void *p, int n, void *heap, int ret);

void *func_020ea1bc(int size, void *heap)
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
        if (allocSize < 0x7c) {
            return 0;
        }
        total = (int) (allocSize - 0x30);
    } else {
        total = ((size + 3) & ~3) + 0x4c;
        allocSize = (u32) (total + 0x30);
    }
    block = func_020e9ed4(heap, allocSize, 4);
    if (block != 0) {
        p = (char *) block + 0x30;
        ret = NNS_FndCreateExpHeapEx(p, total, data_0213e5a4);
        if (ret == 0) {
            func_020e9c48(heap, block);
            block = 0;
        } else if (block != 0) {
            func_020ea41c(block, p, total, heap, ret);
        }
    }
    return block;
}
