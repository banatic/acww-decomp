/* func_0203a23c @ 0x0203a23c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void *func_0203a404(void *);
extern void *func_0203a344(void *);

extern unsigned char data_020da658[];

void *func_0203a23c(void *self)
{
    void *p;

    func_0208af30(self);
    ((unsigned int *) self)[0] = (unsigned int) (unsigned int) data_020da658;
    ((unsigned int *) self)[3] = 0;
    ((unsigned int *) self)[4] = 0;
    ((unsigned int *) self)[5] = 0;
    ((unsigned int *) self)[6] = 0;

    p = self;
    p = (char *) p + 0x1c;
    func_0208a1f8(p);

    p = self;
    p = (char *) p + 0x30;
    func_0208a1f8(p);

    ((unsigned int *) self)[0x11] = 0;
    ((unsigned int *) self)[0x12] = 0;
    ((unsigned int *) self)[0x13] = 0;
    ((unsigned int *) self)[0x14] = 0;

    p = self;
    p = (char *) p + 0x54;
    func_0203a404(p);

    p = self;
    p = (char *) p + 0x88;
    func_0203a344(p);

    ((unsigned int *) self)[0x27] = 0;
    ((unsigned int *) self)[0x28] = 0;
    ((unsigned int *) self)[0x29] = 0;
    ((unsigned int *) self)[0x2a] = 0;
    ((unsigned int *) self)[0x2b] = 0;
    ((unsigned int *) self)[0x2c] = 0;
    ((unsigned char *) self)[0xb4] = 0;

    return self;
}
