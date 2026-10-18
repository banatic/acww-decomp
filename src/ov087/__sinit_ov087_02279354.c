/* __sinit_ov087_02279354 @ 0x02279354, 0x5c bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279354 {
    int a;
    int b;
};
extern int data_ov087_022795c0[];
extern int data_ov087_022793c8[];
extern int data_ov087_022793e0[];
extern int data_ov087_022793e8[];
extern int data_ov087_022793d8[];
extern int __ptmf_null[];
extern int data_ov087_022793d0[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov087_02279354(void)
{
    ((struct UnkStruct_02279354 *) data_ov087_022795c0)[0] = *(const struct UnkStruct_02279354 *) data_ov087_022793c8;
    ((struct UnkStruct_02279354 *) data_ov087_022795c0)[1] = *(const struct UnkStruct_02279354 *) data_ov087_022793e0;
    ((struct UnkStruct_02279354 *) data_ov087_022795c0)[2] = *(const struct UnkStruct_02279354 *) data_ov087_022793e8;
    ((struct UnkStruct_02279354 *) data_ov087_022795c0)[3] = *(const struct UnkStruct_02279354 *) data_ov087_022793d8;
    ((struct UnkStruct_02279354 *) data_ov087_022795c0)[4] = *(const struct UnkStruct_02279354 *) __ptmf_null;
    ((struct UnkStruct_02279354 *) data_ov087_022795c0)[5] = *(const struct UnkStruct_02279354 *) data_ov087_022793d0;
    return (int) data_ov087_022795c0;
}

#pragma section INIT end
