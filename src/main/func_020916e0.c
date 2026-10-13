/* func_020916e0 @ 0x020916e0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct GBase {
    u8 pad_00[0x1c];
    u16 unk_1C;
};

extern struct GBase data_021d5658;
extern u8 data_020e2944;

extern __thumb int func_02094cf8(int, int, int, int, int, int);
extern __thumb int func_02091494(struct GBase *, u16, int, int, int, int, int);
extern __thumb int func_02090ac4(int, int, int, void *);
extern __thumb void func_020914dc(struct GBase *);

int func_020916e0(u32 p0, u32 p1, u32 p2, u32 p3)
{
    void *addr = &data_021d5658;
    int result = 3;

    func_02094cf8(0x13, p0, p1, p2, p3, 0);
    func_02091494(addr, *(u16 *) ((char *) addr + 0x1c), p0, p1, p2, p3, 0x25);
    if (func_02090ac4(0x62, p1, p2, &data_020e2944) != 0) {
        result = 2;
    }
    func_020914dc(&data_021d5658);
    return result;
}
