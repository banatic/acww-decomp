/* func_02032768 @ 0x02032768, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202ff00(void *self);
extern void func_02032758(void *self);
extern char data_020da234;

void *func_02032768(void *self)
{
    func_0202ff00(self);
    *(void **) self = (void *) &data_020da234;
    func_02032758(self);
    return self;
}
