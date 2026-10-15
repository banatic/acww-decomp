/* func_ov047_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov047_02262ca4;
extern void *func_ov047_02261978(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);

struct UnkStruct_02260448 {
    void *unk_00;
    char pad_04[0x654];
};

void *func_ov047_02260448(struct UnkStruct_02260448 *self)
{
    self->unk_00 = &data_ov047_02262ca4;
    func_ov047_02261978((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
