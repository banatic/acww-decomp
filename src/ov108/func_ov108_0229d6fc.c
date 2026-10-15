/* func_ov108_0229d6fc @ 0x0229d6fc, 0x1c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

int func_ov108_0229d6fc(int a)
{
    if (data_021fbdd8 == 0) {
        return (int) func_ov002_02208098((void *) (a), 5);
    }
    return a;
}
