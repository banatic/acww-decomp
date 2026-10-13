/* func_ov137_0229cce4 @ 0x0229cce4, 0x3c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov134_02299af0(void *ptr, unsigned char val);
extern void func_ov134_02299a84(void *ptr);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov137_0229cce4(void *arg)
{
    if (data_021fbdd8) {
        func_ov134_02299af0((char *) arg + 0x2c4, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) arg + 0x2c4);
        func_ov002_02208098(arg, 1);
    }
}
