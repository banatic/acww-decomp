/* func_02002808 @ 0x02002808, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001cc4(int, int, int, int);
extern void func_02001ca0(int, int, int, int);
extern void func_02001c7c(int, int, int, int);
extern void func_02001c58(int, int, int, int);

void func_02002808(unsigned int a, int b, int c, int d, int e)
{
    switch (a) {
        case 0:
            func_02001cc4(b, c, d, e);
            break;
        case 1:
            func_02001ca0(b, c, d, e);
            break;
        case 2:
            func_02001c7c(b, c, d, e);
            break;
        case 3:
            func_02001c58(b, c, d, e);
            break;
        default:
            break;
    }
}
