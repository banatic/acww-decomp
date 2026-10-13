/* func_02011fd8 @ 0x02011fd8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned int uint32_t;

extern void *MI_CpuFill8(void *, int, unsigned int);

struct UnkStruct_02011fd8 {
    char pad_00[0x48];
    uint32_t unk_48;       // 0x48
    uint32_t unk_4C;       // 0x4c
    char buffer[0x200];    // 0x50
    uint32_t unk_250;      // 0x250
    unsigned char unk_254; // 0x254
    unsigned char unk_255; // 0x255
};

struct UnkStruct_02011fd8 *func_02011fd8(struct UnkStruct_02011fd8 *ptr)
{
    ptr->unk_48 = 0;
    ptr->unk_4C = 0;
    ptr->unk_250 = 3;
    ptr->unk_254 = 0;
    ptr->unk_255 = 0;
    MI_CpuFill8(ptr->buffer, 0, 0x200);
    return ptr;
}
