/* func_0203de48 @ 0x0203de48, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a90(void *, unsigned int);
extern char data_020da994[];

void *func_0203de48(void *self)
{
    func_020a9a90(self, 0);
    *(char **) self = data_020da994;
    return self;
}
