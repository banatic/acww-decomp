/* func_ov051_02261038 @ 0x02261038, 0x20 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov051_02261804;
extern void func_0201615c(void *self, void *arg);
extern void func_020edb3c(void *self);

void *func_ov051_02261038(void *self)
{
    *(void **) self = &data_ov051_02261804;
    func_0201615c(self, &data_ov051_02261804);
    func_020edb3c(self);
    return self;
}
