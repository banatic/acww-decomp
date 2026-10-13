/* func_0203ad68 @ 0x0203ad68, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc8];
    int unk_C8;
} UnkStruct_0203ad68;
extern UnkStruct_0203ad68 *data_021c67a4;
extern int func_0203c4e4(UnkStruct_0203ad68 *arg);

void func_0203ad68(void)
{
    data_021c67a4->unk_C8 = func_0203c4e4(data_021c67a4);
}
