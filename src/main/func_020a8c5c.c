/* func_020a8c5c @ 0x020a8c5c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d94;
extern char data_020da6dc;
extern void func_020a9b44(void *ptr);
extern void func_020edb3c(void *ptr);

void *func_020a8c5c(void *obj)
{
    char *self = (char *) obj;
    *(void **) self = &data_020e3d94;
    func_020a9b44(self + 8);
    *(void **) self = &data_020da6dc;
    func_020edb3c(self);
    return obj;
}
