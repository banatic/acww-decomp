/* func_0203a3ec @ 0x0203a3ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *self);
extern char data_020da640;

void *func_0203a3ec(void *self)
{
    *(void **) self = &data_020da640;
    func_020a8c38(self);
    return self;
}
