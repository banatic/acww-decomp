/* __sinit_ov081_02279620 @ 0x02279620, 0x5c bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279620 {
    int a;
    int b;
};
extern int data_ov081_022798b4[];
extern int data_ov081_022796a0[];
extern int data_ov081_022796b8[];
extern int data_ov081_022796d0[];
extern int data_ov081_022796c8[];
extern int __ptmf_null[];
extern int data_ov081_022796c0[];

int __sinit_ov081_02279620(void)
{
    ((struct UnkStruct_02279620 *) data_ov081_022798b4)[0] = *(const struct UnkStruct_02279620 *) data_ov081_022796a0;
    ((struct UnkStruct_02279620 *) data_ov081_022798b4)[1] = *(const struct UnkStruct_02279620 *) data_ov081_022796b8;
    ((struct UnkStruct_02279620 *) data_ov081_022798b4)[2] = *(const struct UnkStruct_02279620 *) data_ov081_022796d0;
    ((struct UnkStruct_02279620 *) data_ov081_022798b4)[3] = *(const struct UnkStruct_02279620 *) data_ov081_022796c8;
    ((struct UnkStruct_02279620 *) data_ov081_022798b4)[4] = *(const struct UnkStruct_02279620 *) __ptmf_null;
    ((struct UnkStruct_02279620 *) data_ov081_022798b4)[5] = *(const struct UnkStruct_02279620 *) data_ov081_022796c0;
    return (int) data_ov081_022798b4;
}
