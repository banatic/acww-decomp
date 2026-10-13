/* func_020369a0 @ 0x020369a0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036f60(void *);
extern void func_020370e4(void *);
extern void func_020372ec(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020da304[];

void *func_020369a0(void *self)
{
    *(int *) self = (unsigned int) data_020da304;
    func_02036f60((char *) self + 0x24);
    func_020370e4((char *) self + 0x18);
    func_020372ec((char *) self + 4);
    func_020edb3c(self);
    return self;
}
