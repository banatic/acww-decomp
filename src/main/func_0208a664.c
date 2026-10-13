/* func_0208a664 @ 0x0208a664, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0208a664 UnkStruct_0208a664;
struct UnkStruct_0208a664 {
    void **vtable;
    unsigned char pad_04[0x30 - 4];
    int unk_30;
};
typedef struct RetStruct {
    int unk_00;
    int unk_04;
} RetStruct;
extern RetStruct *func_0208a1c8(void *p);
extern void func_0208a1e0(void *p, int v, int z);
void func_0208a664(void *self)
{
    u32 r6;
    u32 r7;
    UnkStruct_0208a664 *p0;
    UnkStruct_0208a664 *p1;
    int maxVal;
    int r;
    int slot;
    u32 shift;
    p0 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc0));
    if (p0) {
        r6 = ((int (*)(UnkStruct_0208a664 *)) p0->vtable[3])(p0);
    } else {
        r6 = 0;
    }
    p1 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc4));
    if (p1) {
        maxVal = ((int (*)(UnkStruct_0208a664 *)) p1->vtable[3])(p1);
        r7 = maxVal;
    } else {
        r7 = 0;
    }
    {
        u32 a = (r6 + 7) >> 3;
        u32 b = (r7 + 7) >> 3;
        int r4 = (a > b) ? ((int) a) : ((int) b);
        maxVal = func_0208a1c8(((char *) self) + 0xc)->unk_04 - 1;
        r = r4 - 1;
        slot = maxVal;
        if (r < 0) {
            slot = 0;
        } else if (r <= maxVal) {
            slot = r;
        }
        func_0208a1e0(((char *) self) + 0xc, slot, 0);
        func_0208a1e0(((char *) self) + 0x20, slot, 0);
        if ((*((unsigned char *) (((char *) self) + 0x5c))) != 0) {
            shift = ((u32) r4) << 3;
            p0 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc0));
            if (p0) {
                p0->unk_30 = (shift > r6) ? ((shift - r6) >> 1) : (0);
            }
            p1 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc4));
            if (p1) {
                p1->unk_30 = (shift > r7) ? ((shift - r7) >> 1) : (0);
            }
        } else {
            p0 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc0));
            if (p0) {
                p0->unk_30 = 0;
            }
            p1 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc4));
            if (p1) {
                p1->unk_30 = 0;
            }
        }
    }
}
