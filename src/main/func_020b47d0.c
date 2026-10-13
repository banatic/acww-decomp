/* func_020b47d0 @ 0x020b47d0, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4950_unk(const signed char *str);

void func_020b47d0(signed char *str)
{
    int len;
    unsigned int half;
    unsigned int i;
    int j;
    signed char tmp;

    len = func_020b4950_unk(str);
    half = (unsigned int) len >> 1;
    i = 0;
    j = len - 1;
    while (i < half) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}
