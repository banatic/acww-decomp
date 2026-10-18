/* __sinit_ov083_02279100 @ 0x02279100, 0x5c bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279100 {
    int a;
    int b;
};
extern int data_ov083_02279360[];
extern int data_ov083_02279198[];
extern int data_ov083_022791a0[];
extern int data_ov083_02279190[];
extern int data_ov083_02279188[];
extern int __ptmf_null[];
extern int data_ov083_02279180[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov083_02279100(void)
{
    ((struct UnkStruct_02279100 *) data_ov083_02279360)[0] = *(const struct UnkStruct_02279100 *) data_ov083_02279198;
    ((struct UnkStruct_02279100 *) data_ov083_02279360)[1] = *(const struct UnkStruct_02279100 *) data_ov083_022791a0;
    ((struct UnkStruct_02279100 *) data_ov083_02279360)[2] = *(const struct UnkStruct_02279100 *) data_ov083_02279190;
    ((struct UnkStruct_02279100 *) data_ov083_02279360)[3] = *(const struct UnkStruct_02279100 *) data_ov083_02279188;
    ((struct UnkStruct_02279100 *) data_ov083_02279360)[4] = *(const struct UnkStruct_02279100 *) __ptmf_null;
    ((struct UnkStruct_02279100 *) data_ov083_02279360)[5] = *(const struct UnkStruct_02279100 *) data_ov083_02279180;
    return (int) data_ov083_02279360;
}

#pragma section INIT end
