/* func_ov068_02272f38 @ 0x02272f38, 0x24 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *p);
extern unsigned char data_ov068_02277750[];
extern unsigned char data_ov068_02277814[];

struct UnkStruct_02272f38 {
    unsigned char *unk_00;
    unsigned char pad_04[0xe8];
    unsigned char *unk_EC;
};

struct UnkStruct_02272f38 *func_ov068_02272f38(struct UnkStruct_02272f38 *this)
{
    func_ov009_0226552c(this);
    this->unk_00 = data_ov068_02277750;
    this->unk_EC = data_ov068_02277814;
    return this;
}
