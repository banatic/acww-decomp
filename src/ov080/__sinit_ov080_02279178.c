/* __sinit_ov080_02279178 @ 0x02279178, 0x5c bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279178 {
    int a;
    int b;
};
extern int data_ov080_022793e0[];
extern int data_ov080_022791f8[];
extern int data_ov080_02279200[];
extern int data_ov080_022791f0[];
extern int data_ov080_022791e8[];
extern int __ptmf_null[];
extern int data_ov080_022791e0[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov080_02279178(void)
{
    ((struct UnkStruct_02279178 *) data_ov080_022793e0)[0] = *(const struct UnkStruct_02279178 *) data_ov080_022791f8;
    ((struct UnkStruct_02279178 *) data_ov080_022793e0)[1] = *(const struct UnkStruct_02279178 *) data_ov080_02279200;
    ((struct UnkStruct_02279178 *) data_ov080_022793e0)[2] = *(const struct UnkStruct_02279178 *) data_ov080_022791f0;
    ((struct UnkStruct_02279178 *) data_ov080_022793e0)[3] = *(const struct UnkStruct_02279178 *) data_ov080_022791e8;
    ((struct UnkStruct_02279178 *) data_ov080_022793e0)[4] = *(const struct UnkStruct_02279178 *) __ptmf_null;
    ((struct UnkStruct_02279178 *) data_ov080_022793e0)[5] = *(const struct UnkStruct_02279178 *) data_ov080_022791e0;
    return (int) data_ov080_022793e0;
}

#pragma section INIT end
