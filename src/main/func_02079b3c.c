/* func_02079b3c @ 0x02079b3c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(int);
extern int func_020036e8(int);
extern unsigned char data_020cd500[][6];

int func_02079b3c(int a, int b, int c)
{
    int result = 0;
    if (func_02003704(b) && func_02003704(c)) {
        result = data_020cd500[func_020036e8(b)][func_020036e8(c)];
    }
    return result;
}
