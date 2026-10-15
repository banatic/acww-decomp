/* func_ov126_0229fb58 @ 0x0229fb58, 0x44 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern unsigned int func_020996b8(int object);
extern unsigned int func_0206fc8c(void);
extern unsigned int func_02072bb0(unsigned int, unsigned int);
extern int func_02051c08(unsigned char *, unsigned char *, int);
extern unsigned int func_02072d4c(unsigned int);
extern void func_02072e3c(unsigned int, unsigned char *);

void func_ov126_0229fb58(void *self)
{
    unsigned char buf[0x14];
    unsigned int v;

    v = func_02072bb0(func_020996b8(func_020984e8()), func_0206fc8c());
    func_02051c08((unsigned char *) self + 0x4248, buf, 10);
    func_02072e3c(func_02072d4c(v), buf);
}
