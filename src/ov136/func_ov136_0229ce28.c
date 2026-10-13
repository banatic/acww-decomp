/* func_ov136_0229ce28 @ 0x0229ce28, 0x54 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov134_0229b034(void *ptr);
extern void func_ov002_02208098(void *ptr, int val);
extern void func_ov134_0229b108(void *ptr, unsigned char a, unsigned char b);

void func_ov136_0229ce28(void *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov134_0229b034((char *) self + 0x2c4) != 0) {
            func_ov002_02208098(self, 2);
        } else {
            func_ov002_02208098(self, 0);
        }
    } else {
        func_ov134_0229b108((char *) self + 0x2c4, data_021f6c58, data_021f6c54);
    }
}
