/* func_ov114_0229c890 @ 0x0229c890, 0x24 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229c7d0(void *);
extern int func_ov114_0229d088(void *);

struct UnkStruct_0229c890 {
    unsigned char pad_00[0x12b8];
    unsigned char unk_12B8;
    unsigned char unk_12B9;
};

int func_ov114_0229c890(struct UnkStruct_0229c890 *p)
{
    p->unk_12B8 = p->unk_12B9;
    func_ov114_0229c7d0(p);
    return func_ov114_0229d088(p);
}
