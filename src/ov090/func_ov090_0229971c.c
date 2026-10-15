/* func_ov090_0229971c @ 0x0229971c, 0x58 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f55c(void);
extern void func_ov090_0229915c(void *p);
extern void func_0206ef98(void);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_0206fbb4(void);
extern void func_020041fc(void);
extern void func_0206fe38(void);

extern unsigned char data_ov090_02299960;

int func_ov090_0229971c(char *self)
{
    *(unsigned char *) (self + 0x98) = 1;
    func_0206f55c();
    func_ov090_0229915c(self);
    func_0206ef98();
    *(unsigned char *) (self + 0x96) = 0xff;
    data_ov090_02299960 = 0;
    *(unsigned char *) (self + 0x97) = 0;
    *(unsigned char *) (self + 0x8d) = 1;
    *(unsigned char *) (self + 0x8c) = 0;
    func_ov002_022080a0(self, 0);
    func_0206fbb4();
    func_020041fc();
    func_0206fe38();
    return 1;
}
