/* func_02038bac @ 0x02038bac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020ca0f4[0x18];
extern signed char data_020ca10c[][2];
void func_02038bac(unsigned char *out, signed char *in)
{
    unsigned int c;
    unsigned int i;
    while (*in != 0) {
        c = (unsigned char) *in;
        for (i = 0; i < 0x15; i++) {
            if (c == data_020ca0f4[i]) {
                out[0] = (unsigned char) data_020ca10c[i][0];
                out[1] = (unsigned char) data_020ca10c[i][1];
            }
        }
        in++;
        out += 2;
    }
    out[0] = 0;
    out[1] = 0;
}
