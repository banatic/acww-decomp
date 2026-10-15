/* func_ov051_02261070 @ 0x02261070, 0x18 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020161ac(void *self);
extern char data_ov051_02261804;

void *func_ov051_02261070(void *self)
{
    func_020161ac(self);
    *(void **) self = (void *) &data_ov051_02261804;
    return self;
}
