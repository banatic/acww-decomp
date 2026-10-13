/* func_ov137_0229c750 @ 0x0229c750, 0x44 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov137_0229c574(void *, int);
extern int func_ov134_022999ac(void *);
extern int func_ov002_0220a72c(void *, int);
extern int data_ov137_0229d374[];

int func_ov137_0229c750(void *param)
{
    unsigned char b;

    if (func_ov137_0229c574(param, 2) != 0) {
        return func_ov134_022999ac((char *) param + 0x2c4);
    }
    b = ((unsigned char *) param)[0x2b77];
    if (b == 2) {
        param = (char *) param + 0xf8;
        return func_ov002_0220a72c(param, 6);
    }
    return data_ov137_0229d374[b];
}
