/* func_020545e0 @ 0x020545e0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056ed4(void *);
extern void func_02057078(void *);
extern void func_02054ad0(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020dd07c[];
extern unsigned char data_020dd08c[];
extern unsigned char data_020dd09c[];

void *func_020545e0(void *self)
{
    *(void **) self = (void *) data_020dd07c;
    *(void **) ((char *) self + 0x9c) = (void *) data_020dd08c;
    *(void **) ((char *) self + 0xb8) = (void *) data_020dd09c;
    func_02056ed4((char *) self + 0x170);
    func_02057078((char *) self + 0x158);
    func_02054ad0(self);
    func_020edb3c(self);
    return self;
}
