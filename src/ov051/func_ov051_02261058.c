/* func_ov051_02261058 @ 0x02261058, 0x18 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261058 {
    char *vt;
};

extern char data_ov051_02261804;
extern void func_0201615c(struct UnkStruct_02261058 *p);

struct UnkStruct_02261058 *func_ov051_02261058(struct UnkStruct_02261058 *self)
{
    self->vt = &data_ov051_02261804;
    func_0201615c(self);
    return self;
}
