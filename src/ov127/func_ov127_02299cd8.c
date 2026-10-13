/* func_ov127_02299cd8 @ 0x02299cd8, 0x46 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_02299b58(int a, int b);
extern void func_ov127_02299abc(int a, int b, int c);

void func_ov127_02299cd8(int a, unsigned int sw, int b, int c)
{
    switch (sw) {
        case 0:
            func_ov127_02299b58(a, -b);
            break;
        case 1:
            func_ov127_02299b58(a, b);
            break;
        case 2:
            func_ov127_02299abc(a, b, c);
            break;
        case 3:
            func_ov127_02299abc(a, -b, c);
            break;
        default:
            break;
    }
}
