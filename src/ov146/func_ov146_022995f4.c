/* func_ov146_022995f4 @ 0x022995f4, 0x5c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov146_0229b680;
void func_02070be8(void);

#pragma arm
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
#pragma thumb

void func_ov002_0220a5e4(void *);
void func_ov002_0220b0f4(void *);
void func_ov002_02209cb4(void *);
void func_ov002_0220826c(void *);
void func_ov002_02207f6c(void *);

void *func_ov146_022995f4(void *self)
{
    *(void **) self = &data_ov146_0229b680;
    func_ov002_0220a5e4((char *) self + 0x1fb4);
    func_ov002_0220b0f4((char *) self + 0x1ee8);
    __cxa_vec_cleanup((char *) self + 0x1630, 0x14, 0x6c, func_02070be8);
    func_ov002_02209cb4((char *) self + 0x15cc);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
