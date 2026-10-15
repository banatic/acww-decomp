/* func_ov004_0223d354 @ 0x0223d354, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223cfcc(void *);
extern void func_ov004_0223b13c(void *);
extern unsigned int func_ov004_0223c130(void);
extern void func_ov004_0223a818(void *);
extern void *func_ov004_0223d03c(void);
extern void func_ov004_0223d200(char *);
extern int func_0209d138(void *);
extern void *func_ov004_0223cb10(void);
extern void func_ov004_0223c7b8(char *);
extern void func_ov004_0223cea8(void *);
extern char data_ov004_02259698[];
extern char data_ov004_022595c4[];
extern void *data_ov004_022595c0;

int func_ov004_0223d354(char *self)
{
    func_ov004_0223cfcc(self + 0x50);
    func_ov004_0223b13c(self + 0x1c4);
    if (func_ov004_0223c130() > 1) {
        func_ov004_0223a818(self + 0x64);
    }
    func_ov004_0223d200((char *) func_ov004_0223d03c());
    func_0209d138(data_ov004_02259698);
    data_ov004_022595c0 = 0;
    func_ov004_0223c7b8((char *) func_ov004_0223cb10());
    func_ov004_0223cea8(data_ov004_022595c4);
    return 1;
}
