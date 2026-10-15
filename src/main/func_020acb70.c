/* func_020acb70 @ 0x020acb70, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208ec14(void *);
extern void func_0208af00(void *);
extern char data_020e4014;

void *func_020acb70(void *self)
{
    *(void **) self = &data_020e4014;
    func_0208ec14((char *) self + 0x10);
    func_0208af00(self);
    return self;
}
