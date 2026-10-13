/* func_020a008c @ 0x020a008c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    unsigned int unk_64;
    char pad_68[0x58];
    unsigned int unk_C0;
    char pad_C4[0x1000];
    unsigned int unk_10C4;
    unsigned char unk_10C8;
} UnkStruct_020a008c;

extern void MI_CpuFill8(void *dest, unsigned char data, unsigned int size);

int func_020a008c(UnkStruct_020a008c *p)
{
    p->unk_C0 = 0x3039;
    p->unk_10C4 = 0x3039;
    p->unk_10C8 = 0;
    MI_CpuFill8(p, 0, 0xC0);
    p->unk_64 = 2;
    return 2;
}
