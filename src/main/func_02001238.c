/* func_02001238 @ 0x02001238, 0x30 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213fdc0;

void func_02001238(int unused, int b, int c)
{
    if (c == 0) {
        if ((b & 0xff) == 0) {
            data_0213fdc0 = 1;
            return;
        }
    }
    data_0213fdc0 = 2;
}
