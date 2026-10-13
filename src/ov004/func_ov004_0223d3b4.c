/* func_ov004_0223d3b4 @ 0x0223d3b4, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223cfec(void *);
extern void func_ov004_0223cfd4(void *);
extern unsigned int func_ov004_0223c130(void);
extern int func_02050974(void *);
extern int func_020b67ac(void);
extern int func_020b6788(void);
extern void func_ov004_0223a9e0(void *);
extern void func_ov004_0223bdac(void *);
extern void func_ov004_0223a9b8(void *);
extern void func_ov004_0223bf40(void *);
extern void func_ov004_0223bfe0(void *);
extern void *func_ov004_0223cb10(void);
extern void func_ov004_0223c7b8(void *);
extern unsigned short data_ov004_022595bc;
extern char data_021c8188;

int func_ov004_0223d3b4(char *self)
{
    func_ov004_0223cfec(self + 0x50);
    func_ov004_0223cfd4(self + 0x50);
    data_ov004_022595bc = (data_ov004_022595bc + 1) % 0x28;
    if (func_ov004_0223c130() > 1 && func_02050974(&data_021c8188) == 4 && func_020b67ac() == 0 && func_020b6788() == 0) {
        func_ov004_0223a9e0(self + 0x64);
        func_ov004_0223bdac(self);
        func_ov004_0223a9b8(self + 0x64);
    }
    func_ov004_0223bf40(self);
    func_ov004_0223bfe0(self);
    func_ov004_0223c7b8(func_ov004_0223cb10());
    return 1;
}
