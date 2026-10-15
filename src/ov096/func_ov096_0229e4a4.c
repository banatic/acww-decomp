/* func_ov096_0229e4a4 @ 0x0229e4a4, 0x54 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern unsigned short *func_02099710(void *);
extern unsigned short *func_020996e0(void *);
extern unsigned short *func_020996f8(void *);
extern unsigned short *func_02099728(void *);

int func_ov096_0229e4a4(int a, int b)
{
    void *p = func_020984e8();
    switch (b) {
        case 2:
            return *func_02099710(p);
        case 3:
            return *func_020996e0(p);
        case 4:
            return *func_020996f8(p);
        case 5:
            return *func_02099728(p);
        default:
            return 0xFFF1;
    }
}
