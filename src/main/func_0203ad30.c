/* func_0203ad30 @ 0x0203ad30, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203ad30 {
    char pad_00[0xc8];
    int unk_C8;
} UnkStruct_0203ad30;

extern UnkStruct_0203ad30 *data_021c67a4;
extern int func_0203c4e4(UnkStruct_0203ad30 *ptr);

unsigned char func_0203ad30(void)
{
    int a = func_0203c4e4(data_021c67a4);
    int b = data_021c67a4->unk_C8;
    return (unsigned char) ((a - b) >> 12);
}
