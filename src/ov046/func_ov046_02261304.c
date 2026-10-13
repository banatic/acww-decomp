/* func_ov046_02261304 @ 0x02261304, 0x18 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02261304 UnkStruct_02261304;
struct UnkStruct_02261304 {
    void *unk_00;
};

extern void func_0202eb70(UnkStruct_02261304 *this);
extern char data_ov046_0226204c;

UnkStruct_02261304 *func_ov046_02261304(UnkStruct_02261304 *this)
{
    func_0202eb70(this);
    this->unk_00 = &data_ov046_0226204c;
    return this;
}
