/* __sinit_ov085_02279368 @ 0x02279368, 0x5c bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279368 {
    int a;
    int b;
};
extern int data_ov085_022795e0[];
extern int data_ov085_022793f8[];
extern int data_ov085_02279400[];
extern int data_ov085_022793f0[];
extern int data_ov085_022793e8[];
extern int __ptmf_null[];
extern int data_ov085_022793e0[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov085_02279368(void)
{
    ((struct UnkStruct_02279368 *) data_ov085_022795e0)[0] = *(const struct UnkStruct_02279368 *) data_ov085_022793f8;
    ((struct UnkStruct_02279368 *) data_ov085_022795e0)[1] = *(const struct UnkStruct_02279368 *) data_ov085_02279400;
    ((struct UnkStruct_02279368 *) data_ov085_022795e0)[2] = *(const struct UnkStruct_02279368 *) data_ov085_022793f0;
    ((struct UnkStruct_02279368 *) data_ov085_022795e0)[3] = *(const struct UnkStruct_02279368 *) data_ov085_022793e8;
    ((struct UnkStruct_02279368 *) data_ov085_022795e0)[4] = *(const struct UnkStruct_02279368 *) __ptmf_null;
    ((struct UnkStruct_02279368 *) data_ov085_022795e0)[5] = *(const struct UnkStruct_02279368 *) data_ov085_022793e0;
    return (int) data_ov085_022795e0;
}

#pragma section INIT end
