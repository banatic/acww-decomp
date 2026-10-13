/* func_02014a44 @ 0x02014a44, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(void *ptr, int id);

int func_02014a44(unsigned char *data, unsigned char val)
{
    if (func_0201596c(data, 0xB)) {
        data[0xA4] = val;
        return 1;
    }
    return 0;
}
