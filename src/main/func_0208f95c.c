/* func_0208f95c @ 0x0208f95c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208f95c {
    unsigned char pad_00[0xc];
    unsigned short unk_0C;
} UnkStruct_0208f95c;

typedef struct UnkStruct_0208f95c_2 {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
} UnkStruct_0208f95c_2;

extern UnkStruct_0208f95c *data_021f42f4;
extern UnkStruct_0208f95c_2 data_021d3654;
extern unsigned char data_020d0ba8[];

void func_0208f95c(int param)
{
    if (data_021f42f4->unk_0C == 5) {
        return;
    }
    data_021d3654.unk_28 = data_020d0ba8[param];
}
