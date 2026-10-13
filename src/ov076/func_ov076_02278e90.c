/* func_ov076_02278e90 @ 0x02278e90, 0x24 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *);
extern char data_ov076_02279744;

struct UnkStruct_02278e90 {
    void *unk_00;
    char pad_04[0xB4];
    unsigned short unk_B8;
};

struct UnkStruct_02278e90 *func_ov076_02278e90(struct UnkStruct_02278e90 *this)
{
    func_0202eb70(this);
    this->unk_00 = &data_ov076_02279744;
    this->unk_B8 = 0xFFF1;
    return this;
}
