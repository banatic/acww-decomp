/* func_0203aeac @ 0x0203aeac, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203aeac {
    char pad_00[0x1fc];
    int unk_1FC;
} UnkStruct_0203aeac;

extern UnkStruct_0203aeac *data_021c67a4;
extern int func_0203c0ac(UnkStruct_0203aeac *p, int val);

int func_0203aeac(void)
{
    return func_0203c0ac(data_021c67a4, data_021c67a4->unk_1FC);
}
