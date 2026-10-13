/* func_02037c78 @ 0x02037c78, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037cc0(short *p, short *q, unsigned int index);

int func_02037c78(short *p, unsigned int a, unsigned int b)
{
    int result = 0;
    if (a < 16 && b < 16) {
        result = func_02037cc0(p, p + b, a);
    }
    return result;
}
