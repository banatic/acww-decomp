/* __sinit_020c7320 @ 0x020c7320, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020c7320 {
    int a;
    int b;
};
extern int data_021fbd90[];
extern int data_020e7f78[];
extern int data_020e7f90[];
extern int data_020e7f50[];
extern int data_020e7f58[];
extern int __ptmf_null[];
extern int data_020e7f70[];
extern int data_020e7f60[];
extern int data_020e7f80[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_020c7320(void)
{
    ((struct UnkStruct_020c7320 *) data_021fbd90)[0] = *(const struct UnkStruct_020c7320 *) data_020e7f78;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[1] = *(const struct UnkStruct_020c7320 *) data_020e7f90;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[2] = *(const struct UnkStruct_020c7320 *) data_020e7f50;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[3] = *(const struct UnkStruct_020c7320 *) data_020e7f58;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[4] = *(const struct UnkStruct_020c7320 *) __ptmf_null;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[5] = *(const struct UnkStruct_020c7320 *) data_020e7f70;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[6] = *(const struct UnkStruct_020c7320 *) data_020e7f60;
    ((struct UnkStruct_020c7320 *) data_021fbd90)[7] = *(const struct UnkStruct_020c7320 *) data_020e7f80;
    return (int) data_021fbd90;
}

#pragma section INIT end
