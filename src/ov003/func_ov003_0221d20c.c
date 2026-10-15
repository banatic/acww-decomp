/* func_ov003_0221d20c @ 0x0221d20c, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02238dbc;
extern char data_ov003_02238e80;
extern void *func_ov009_0226539c(void *self);

struct UnkStruct_0221d20c {
    void *unk_00;
    char pad_04[0xE8];
    void *unk_EC;
};

void *func_ov003_0221d20c(void *self)
{
    struct UnkStruct_0221d20c *obj = (struct UnkStruct_0221d20c *) self;
    obj->unk_00 = &data_ov003_02238dbc;
    obj->unk_EC = &data_ov003_02238e80;
    func_ov009_0226539c(self);
    return self;
}
