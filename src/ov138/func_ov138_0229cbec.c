/* func_ov138_0229cbec @ 0x0229cbec, 0x58 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299a90(void *);
extern int func_ov134_02299a84(void *);
extern void func_ov002_0220a0b4(void *, void *, void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov138_0229c7a8(void *);
extern int func_ov138_0229c754(void *);
extern unsigned short data_021fbe40;

void func_ov138_0229cbec(void *self)
{
    if (data_021fbe40 & 1) {
        func_ov134_02299a90((char *) self + 0x2c8);
        func_ov002_0220a0b4((char *) self + 0x98, (void *) func_ov138_0229c7a8(self), (void *) func_ov138_0229c754(self));
    } else {
        func_ov134_02299a84((char *) self + 0x2c8);
        func_ov002_02208098((void *) (self), 7);
    }
}
