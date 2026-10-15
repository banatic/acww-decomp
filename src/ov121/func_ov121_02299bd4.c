/* func_ov121_02299bd4 @ 0x02299bd4, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern unsigned short *func_02099710(unsigned int object);
extern unsigned short *func_020996f8(int object);
extern unsigned short *func_02099728(unsigned int object);

unsigned short func_ov121_02299bd4(int a, int b)
{
    unsigned short result;
    int object = func_020984e8();
    switch (b) {
        case 0:
            result = *func_02099710((unsigned int) object);
            break;
        case 1:
            result = *func_020996f8(object);
            break;
        case 2:
            result = *func_02099728((unsigned int) object);
            break;
        default:
            result = 0xfff1;
            break;
    }
    return result;
}
