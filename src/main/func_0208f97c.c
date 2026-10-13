/* func_0208f97c @ 0x0208f97c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0208f97c {
    char pad_00[0xc];
    unsigned short unk_0C;
} *data_021f42f4;
extern struct UnkStruct_0208f97c_3 {
    int pad_00;
} *data_020ccf94;
extern int func_02073d90(struct UnkStruct_0208f97c_3 *);
extern unsigned char data_020d0ba4[];
extern struct UnkStruct_0208f97c_2 {
    char pad_00[0x24];
    int unk_24;
} data_021d3654;

void func_0208f97c(int param0)
{
    unsigned short f;
    int r;

    f = data_021f42f4->unk_0C;
    r = func_02073d90(data_020ccf94);
    if (f != 5 && r != 0) {
        data_021d3654.unk_24 = data_020d0ba4[param0];
    }
}
