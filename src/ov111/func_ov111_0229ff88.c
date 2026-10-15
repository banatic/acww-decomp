/* func_ov111_0229ff88 @ 0x0229ff88, 0x6c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_0229f994(void *);
extern void func_ov095_0229c084(void *, int);
extern int func_0206f504(void);
extern int func_02051c08(int, void *, int);
extern void func_020953a0(void);
extern int func_020ee45c(void *);
extern int func_ov090_02298f74(int);
extern void func_ov111_0229efc8(void *, int);

void func_ov111_0229ff88(void *self)
{
    *(unsigned short *) ((char *) self + 0xa4) = 0;
    *(unsigned char *) ((char *) self + 0x99) = 0;
    *(unsigned char *) ((char *) self + 0x9a) = 0;
    *(unsigned char *) ((char *) self + 0x9b) = 0;
    *(unsigned char *) ((char *) self + 0xa2) = 0;
    func_ov111_0229f994(self);
    *(int *) ((char *) self + 0xa8) = 0;
    func_ov095_0229c084((char *) self + 0xac, 0);
    func_02051c08(func_0206f504(), (char *) self + 0x3d16, 0x10);
    func_020953a0();
    if (func_ov090_02298f74(func_020ee45c(self))) {
        func_ov111_0229efc8(self, 0x20);
    }
}
