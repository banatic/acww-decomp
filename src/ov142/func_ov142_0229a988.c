/* func_ov142_0229a988 @ 0x0229a988, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov142_0229a6f8(void *a, void *b, unsigned int c, unsigned int d, unsigned int e);
typedef struct {
    char pad_00[0xc6];
    unsigned short unk_C6;
    char pad_C8[0x10];
    unsigned short unk_D8;
} UnkStruct_0229a988;
void func_ov142_0229a988(UnkStruct_0229a988 *p)
{
    p->unk_D8 = 0;
    p->unk_C6 = func_ov142_0229a6f8(p, (char *) p + 0x11d8, 0x1100, 0x44, 1);
}
