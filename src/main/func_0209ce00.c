/* func_0209ce00 @ 0x0209ce00, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209cc30(int, int, int);
extern int func_0209d034(int);

void func_0209ce00(int arg0, unsigned char *out)
{
    unsigned int i, j;
    unsigned int start = 0;
    for (i = 0; i < 6; i++) {
        for (j = start; j < 6; j++) {
            *out++ = (unsigned char) func_0209d034(func_0209cc30(arg0, (int) j, (int) i));
        }
    }
}
