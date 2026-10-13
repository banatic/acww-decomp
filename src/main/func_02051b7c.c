/* func_02051b7c @ 0x02051b7c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee660(void *);
extern int data_020da13c;
extern int data_020dcf40;

void *func_02051b7c(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) &data_020da13c;
    *(void **) self = (void *) &data_020dcf40;
    return self;
}
