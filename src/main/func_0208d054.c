/* func_0208d054 @ 0x0208d054, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern void func_0208d054(unsigned char *arg0);

void func_0208d054(unsigned char *arg0)
{
    unsigned char val;
    unsigned char val2;

    val2 = 1;
    arg0[0xa8] = val2;
    val = data_020e54a8;
    if (val != 1) {
        val2 = 0;
    }
    if (val2 == 0) {
        val = 0;
    } else {
        val = 1;
    }
    arg0[0xa9] = val;
    return;
}
