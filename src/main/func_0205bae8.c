/* func_0205bae8 @ 0x0205bae8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021e5a2c;
extern int func_0207cec0(void *, int);
extern unsigned char func_0207f30c(unsigned char *);

void func_0205bae8(unsigned short *out, int unused, int c)
{
    unsigned char *tested_value0;
    if ((tested_value0 = (unsigned char *) (func_0207cec0(&data_021e5a2c, c))) != 0) {
        unsigned int v = func_0207f30c(tested_value0);
        unsigned short val;
        if (v < 0x44) {
            val = (unsigned short) (v + 0x1100);
        } else {
            val = 0x1100;
        }
        *out = val;
    } else {
        *out = 0x1100;
    }
}
