/* func_02038a90 @ 0x02038a90, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02038c54(void *ptr);
extern void *func_02038cb4(void *ptr);
extern void *func_02038d18(void *ptr);
extern void *func_02055764(void *ptr);

extern unsigned char data_020da520[];

void *func_02038a90(void *self)
{
    *(void **) self = (void *) data_020da520;
    func_02038c54((void *) ((char *) self + 0x250));
    func_02038cb4((void *) ((char *) self + 0x1FC));
    func_02038d18((void *) ((char *) self + 0xE8));
    func_02055764((void *) ((char *) self + 4));
    return self;
}
