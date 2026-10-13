/* func_ov129_0229c2d8 @ 0x0229c2d8, 0x24 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229bf30(void *p, unsigned short value);

typedef struct {
    char pad_00[0xA6];
    unsigned short unk_A6;
} UnkStruct_0229c2d8;

void func_ov129_0229c2d8(UnkStruct_0229c2d8 *p)
{
    if (p->unk_A6 != 0xFFFF) {
        func_ov129_0229bf30(p, p->unk_A6);
        p->unk_A6 = 0xFFFF;
    }
}
