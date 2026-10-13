/* func_ov142_0229b698 @ 0x0229b698, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov142_02299ba4(int param, unsigned char flag, int value);
extern void func_ov142_02299b94(int param);
extern void func_ov002_02208098(int param, int value);

void func_ov142_0229b698(int param)
{
    if (data_021fbdd8) {
        func_ov142_02299ba4(param, data_021f6c54, 1);
    } else {
        func_ov142_02299b94(param);
        func_ov002_02208098(param, 0);
    }
}
