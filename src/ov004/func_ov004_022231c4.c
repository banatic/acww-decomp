/* func_ov004_022231c4 @ 0x022231c4, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern int func_0202ea80(int a, int b);
extern int func_ov004_02222b3c(void *self);
extern void func_ov004_02222b24(void *self, unsigned int k);
extern void func_0203e020(void *self);
extern void func_ov004_02223388(void *self, int a);

int func_ov004_022231c4(char *self)
{
    unsigned int k;

    if (func_02014868(self + 0x618) != 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        if (func_0202ea80(0x11, 1) == 0) {
            k = (unsigned char) (func_ov004_02222b3c(self) + 1);
            if (k > 0xf) {
                k = 0xf;
            }
            func_ov004_02222b24(self, k);
        }
    }
    func_0203e020(self);
    func_ov004_02223388(self, 2);
    return 1;
}
