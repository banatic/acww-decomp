/* func_ov003_0221ee74 @ 0x0221ee74, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221ee74 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
};

extern char data_ov003_022398e8;
extern char data_ov003_022399ac;
extern void func_ov009_0226539c(struct UnkStruct_0221ee74 *);
extern void func_020edf54(struct UnkStruct_0221ee74 *);

struct UnkStruct_0221ee74 *func_ov003_0221ee74(struct UnkStruct_0221ee74 *this)
{
    this->unk_00 = &data_ov003_022398e8;
    this->unk_EC = &data_ov003_022399ac;
    func_ov009_0226539c(this);
    func_020edf54(this);
    return this;
}
