/* __sinit_ov055_02260db4 @ 0x02260db4, 0x9c bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260db4 {
    int a;
    int b;
};
extern int data_ov055_02260f0c[];
extern int __ptmf_null[];
extern int data_ov055_02260e84[];
extern int data_ov055_02260e94[];
extern int data_ov055_02260e64[];
extern int data_ov055_02261084[];
extern int data_ov055_02260e74[];
extern int data_ov055_02260e9c[];
extern int data_ov055_02260e6c[];
extern int data_ov055_02260ea4[];
extern int data_ov055_02260e8c[];
extern int data_ov055_02260e7c[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_ov055_02260db4(void)
{
    ((struct UnkStruct_02260db4 *) data_ov055_02260f0c)[0] = *(const struct UnkStruct_02260db4 *) __ptmf_null;
    *(struct UnkStruct_02260db4 *) ((char *) ((int) data_ov055_02260f0c) + (12)) =
        *(const struct UnkStruct_02260db4 *) data_ov055_02260e84;
    ((struct UnkStruct_02260db4 *) data_ov055_02260f0c)[3] = *(const struct UnkStruct_02260db4 *) data_ov055_02260e94;
    *(struct UnkStruct_02260db4 *) ((char *) ((int) data_ov055_02260f0c) + (36)) =
        *(const struct UnkStruct_02260db4 *) data_ov055_02260e64;
    ((struct UnkStruct_02260db4 *) data_ov055_02261084)[0] = *(const struct UnkStruct_02260db4 *) data_ov055_02260e74;
    ((struct UnkStruct_02260db4 *) data_ov055_02261084)[1] = *(const struct UnkStruct_02260db4 *) data_ov055_02260e9c;
    ((struct UnkStruct_02260db4 *) data_ov055_02261084)[2] = *(const struct UnkStruct_02260db4 *) data_ov055_02260e6c;
    ((struct UnkStruct_02260db4 *) data_ov055_02261084)[3] = *(const struct UnkStruct_02260db4 *) data_ov055_02260ea4;
    ((struct UnkStruct_02260db4 *) data_ov055_02261084)[4] = *(const struct UnkStruct_02260db4 *) data_ov055_02260e8c;
    ((struct UnkStruct_02260db4 *) data_ov055_02261084)[5] = *(const struct UnkStruct_02260db4 *) data_ov055_02260e7c;
    return (int) data_ov055_02261084;
}

#pragma section INIT end
