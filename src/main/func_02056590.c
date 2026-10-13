/* func_02056590 @ 0x02056590, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd154[];
extern void func_02057054(void *);
extern void func_020edb3c(void *);

void *func_02056590(void *self)
{
    *(void **) self = data_020dd154;
    func_02057054(self);
    func_020edb3c(self);
    return self;
}
