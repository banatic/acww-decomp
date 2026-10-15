/* func_ov055_02260478 @ 0x02260478, 0x5c bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern int func_02090020(void *);
extern char *func_020901a0(void *);
extern void *func_ov055_02260a40(void *);
extern int func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov055_02260fd4[];

void *func_ov055_02260478(void *self)
{
    *(void **) self = (void *) data_ov055_02260fd4;
    func_02090020((char *) self + 0x1abc);
    func_020901a0((char *) self + 0x116c);
    func_02090020((char *) self + 0x1064);
    func_020901a0((char *) self + 0x714);
    func_ov055_02260a40((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
