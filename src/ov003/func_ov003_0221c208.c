/* func_ov003_0221c208 @ 0x0221c208, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02238630;
extern char data_ov003_022386f4;
extern void func_ov009_0226539c(void *);

typedef struct {
    void *unk_00;
    char pad_04[0xE8];
    void *unk_EC;
} UnkStruct_0221c208;

void *func_ov003_0221c208(UnkStruct_0221c208 *this)
{
    this->unk_00 = &data_ov003_02238630;
    this->unk_EC = &data_ov003_022386f4;
    func_ov009_0226539c(this);
    return this;
}
