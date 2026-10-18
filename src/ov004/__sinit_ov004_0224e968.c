/* __sinit_ov004_0224e968 @ 0x0224e968, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0224e968 {
    int a;
    int b;
};
extern int data_ov004_02258204[];
extern int data_ov004_022549c4[];
extern int data_ov004_022549cc[];
extern int data_ov004_022549d4[];
extern int data_ov004_022549dc[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov004_0224e968(void)
{
    ((struct UnkStruct_0224e968 *) data_ov004_02258204)[0] = *(const struct UnkStruct_0224e968 *) data_ov004_022549c4;
    ((struct UnkStruct_0224e968 *) data_ov004_02258204)[1] = *(const struct UnkStruct_0224e968 *) data_ov004_022549cc;
    ((struct UnkStruct_0224e968 *) data_ov004_02258204)[2] = *(const struct UnkStruct_0224e968 *) data_ov004_022549d4;
    ((struct UnkStruct_0224e968 *) data_ov004_02258204)[3] = *(const struct UnkStruct_0224e968 *) data_ov004_022549dc;
    return (int) data_ov004_02258204;
}

#pragma section INIT end
