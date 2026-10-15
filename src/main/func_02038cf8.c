/* func_02038cf8 @ 0x02038cf8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);
extern int data_020da530;

void *func_02038cf8(void *self)
{
    *(int *) self = (int) &data_020da530;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
