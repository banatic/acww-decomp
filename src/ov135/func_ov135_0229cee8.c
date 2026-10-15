/* func_ov135_0229cee8 @ 0x0229cee8, 0x54 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov134_0229b034(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov134_0229b108(void *ptr, unsigned char a, unsigned char b);

void func_ov135_0229cee8(void *param)
{
    if (data_021fbdd8 == 0) {
        if (func_ov134_0229b034((char *) param + 0x2c8) != 0) {
            func_ov002_02208098((void *) (param), 2);
        } else {
            func_ov002_02208098((void *) (param), 0);
        }
    } else {
        func_ov134_0229b108((char *) param + 0x2c8, data_021f6c58, data_021f6c54);
    }
}
