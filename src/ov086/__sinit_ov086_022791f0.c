/* __sinit_ov086_022791f0 @ 0x022791f0, 0x5c bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022791f0 {
    int a;
    int b;
};
extern int data_ov086_02279480[];
extern int data_ov086_02279268[];
extern int data_ov086_02279280[];
extern int data_ov086_02279288[];
extern int data_ov086_02279278[];
extern int __ptmf_null[];
extern int data_ov086_02279270[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov086_022791f0(void)
{
    ((struct UnkStruct_022791f0 *) data_ov086_02279480)[0] = *(const struct UnkStruct_022791f0 *) data_ov086_02279268;
    ((struct UnkStruct_022791f0 *) data_ov086_02279480)[1] = *(const struct UnkStruct_022791f0 *) data_ov086_02279280;
    ((struct UnkStruct_022791f0 *) data_ov086_02279480)[2] = *(const struct UnkStruct_022791f0 *) data_ov086_02279288;
    ((struct UnkStruct_022791f0 *) data_ov086_02279480)[3] = *(const struct UnkStruct_022791f0 *) data_ov086_02279278;
    ((struct UnkStruct_022791f0 *) data_ov086_02279480)[4] = *(const struct UnkStruct_022791f0 *) __ptmf_null;
    ((struct UnkStruct_022791f0 *) data_ov086_02279480)[5] = *(const struct UnkStruct_022791f0 *) data_ov086_02279270;
    return (int) data_ov086_02279480;
}

#pragma section INIT end
