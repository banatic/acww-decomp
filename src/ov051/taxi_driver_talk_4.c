/* taxi_driver_talk_4: 3 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_02261070 @ 0x02261070, 0x18 bytes, Thumb
 * func_ov051_02261058 @ 0x02261058, 0x18 bytes, Thumb
 * func_ov051_02261038 @ 0x02261038, 0x20 bytes, Thumb
 */

struct UnkStruct_02261058 {
    char *vt;
};

extern void *func_020161ac(void *self);
extern char data_ov051_02261804;
extern void *func_0201615c(struct UnkStruct_02261058 *p);
extern void func_020edb3c(void *self);

void *func_ov051_02261070(void *self)
{
    func_020161ac(self);
    *(void **) self = (void *) &data_ov051_02261804;
    return self;
}

struct UnkStruct_02261058 *func_ov051_02261058(struct UnkStruct_02261058 *self)
{
    self->vt = &data_ov051_02261804;
    func_0201615c(self);
    return self;
}

void *func_ov051_02261038(void *self)
{
    *(void **) self = &data_ov051_02261804;
    func_0201615c((struct UnkStruct_02261058 *) self);
    func_020edb3c(self);
    return self;
}
