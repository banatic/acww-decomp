/* func_ov050_02263640 @ 0x02263640, 0x6 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02263640;
void func_ov050_02263640(UnkStruct_02263640 *p, unsigned long v)
{
    p->unk_B0 = v;
}
