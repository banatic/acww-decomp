/* func_0203194c @ 0x0203194c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int a, int b);
extern unsigned char data_020c9094[];
extern unsigned char data_020c9095[];
extern unsigned char data_020c9096[];
extern unsigned char data_020c9097[];
extern unsigned char data_020c9048[4];

int func_0203194c(unsigned char *out, int a, int b)
{
    int idx;
    int off;
    idx = func_01ffcb2c(a, b);
    if (idx < 0x7c) {
        off = idx * 30;
        out[0] = data_020c9094[off];
        out[1] = data_020c9095[off];
        out[2] = data_020c9096[off];
        out[3] = data_020c9097[off];
        return 1;
    } else {
        out[0] = data_020c9048[0];
        out[1] = data_020c9048[1];
        out[2] = data_020c9048[2];
        out[3] = data_020c9048[3];
        return 0;
    }
}
