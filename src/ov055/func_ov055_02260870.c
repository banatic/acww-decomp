/* func_ov055_02260870 @ 0x02260870, 0x6 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_02260870;
void func_ov055_02260870(UnkStruct_02260870 *p, unsigned long v)
{
    p->unk_B4 = v;
}
