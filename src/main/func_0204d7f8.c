/* func_0204d7f8 @ 0x0204d7f8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80c8;
extern int func_0204d708(void *p, int a, int b, int c, int d);

int func_0204d7f8(int a, int b, int c, int d)
{
    int result = 0;

    if (data_021c80c8) {
        result = func_0204d708(data_021c80c8, a, b, c, d);
    }
    return result;
}
