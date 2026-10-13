/* func_02079410 @ 0x02079410, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02079410(unsigned char *arg0, int arg1);

void func_02079410(unsigned char *arg0, int arg1)
{
    unsigned short val;
    unsigned char val2;

    if (arg1 == 0) {
        val2 = arg0[2];
        if (val2 != 0) {
            val2--;
            arg0[2] = val2;
        } else {
            val = *(unsigned short *) arg0;
            if (val != 0) {
                val--;
                *(unsigned short *) arg0 = val;
            }
        }
        val = *(unsigned short *) arg0;
        if (val == 0) {
            arg0[3] = 0;
        }
    }
    return;
}
