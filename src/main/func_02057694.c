/* func_02057694 @ 0x02057694, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057640(void *);
extern void func_02057764(void *);
extern void *func_020578d4(void *);
extern void func_02057054(void *);

extern unsigned char data_020dd194[];

void *func_02057694(void *self)
{
    *(void **) self = (void *) data_020dd194;
    func_02057640(self);
    func_02057764((char *) self + 0x65);
    func_02057764((char *) self + 0x54);
    func_020578d4((char *) self + 0x18);
    func_02057054(self);
    return self;
}
