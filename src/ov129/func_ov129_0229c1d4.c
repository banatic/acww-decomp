/* func_ov129_0229c1d4 @ 0x0229c1d4, 0x24 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229bf30(void *p, unsigned short value);

typedef struct {
    char pad_00[0xa8];
    unsigned short unk_A8;
} UnkStruct_0229c1d4;

void func_ov129_0229c1d4(UnkStruct_0229c1d4 *p)
{
    if (p->unk_A8 != 0xFFFF) {
        func_ov129_0229bf30(p, p->unk_A8);
        p->unk_A8 = 0xFFFF;
    }
}
