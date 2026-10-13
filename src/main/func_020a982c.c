/* func_020a982c @ 0x020a982c, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020a982c {
    u32 unk_00;    // 0x00
    u32 unk_04;    // 0x04
    u32 unk_08;    // 0x08
    u32 unk_0C;    // 0x0c
    u8 unk_10;     // 0x10
    u8 pad_11[11]; // 0x11..0x1b
    u32 unk_1C;    // 0x1c
};

extern struct UnkStruct_020a982c data_021f446c;
extern u32 data_021f4470; // 0x021f4470
extern u32 data_021f4474; // 0x021f4474
extern u32 data_021f4478; // 0x021f4478
extern u32 data_021f447c; // 0x021f447c
extern u32 data_021f4488; // 0x021f4488

void func_02064658(void *dst, void *src, u32 size, int flag);
u32 func_020a9ae8(void *addr);
u32 func_020a9ae4(void *addr);
u32 func_020a9adc(void *addr);

int func_020a982c(void *ptr)
{
    int ok1, ok2, ok3;

    func_02064658((char *) ptr + 0x44, &data_021f446c, 0x20, 0);

    data_021f446c.unk_00 = func_020a9ae8(&data_021f446c);
    data_021f446c.unk_04 = func_020a9ae8(&data_021f4470);
    data_021f446c.unk_08 = func_020a9ae4(&data_021f4474);
    data_021f446c.unk_0C = func_020a9ae4(&data_021f4478);
    data_021f446c.unk_10 = (u8) func_020a9adc(&data_021f447c);
    data_021f446c.unk_1C = func_020a9ae4(&data_021f4488);

    ok1 = (data_021f446c.unk_04 == 0x626d6731);
    ok2 = (data_021f446c.unk_08 != 0);
    ok3 = (data_021f446c.unk_0C == 2);

    if (data_021f446c.unk_00 == 0x4d455347 && ok1 && ok2 && ok3) {
        return 1;
    }
    return 0;
}
