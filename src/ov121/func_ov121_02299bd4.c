/* func_ov121_02299bd4 @ 0x02299bd4, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(int a, int b);
extern unsigned short *func_02099710(void);
extern unsigned short *func_020996f8(void);
extern unsigned short *func_02099728(void);

unsigned short func_ov121_02299bd4(int a, int b)
{
    unsigned short result;
    func_020984e8(a, b);
    switch (b) {
        case 0:
            result = *func_02099710();
            break;
        case 1:
            result = *func_020996f8();
            break;
        case 2:
            result = *func_02099728();
            break;
        default:
            result = 0xfff1;
            break;
    }
    return result;
}
