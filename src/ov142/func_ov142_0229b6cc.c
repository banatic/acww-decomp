/* func_ov142_0229b6cc @ 0x0229b6cc, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;

extern void func_ov142_02299ba4(int arg0, unsigned char arg1, int arg2);
extern void func_ov142_02299b94(void *argument0);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov142_0229b6cc(int arg0)
{
    if (data_021fbdd8) {
        func_ov142_02299ba4(arg0, data_021f6c54, 0);
    } else {
        func_ov142_02299b94((void *) arg0);
        func_ov002_02208098((void *) (arg0), 0);
    }
}
