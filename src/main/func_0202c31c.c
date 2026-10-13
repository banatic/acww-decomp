/* func_0202c31c @ 0x0202c31c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202c934(void *out, const void *src, int mode, int param, int size);

extern unsigned char data_020c892c[];

int func_0202c31c(int unused, int *out, int param)
{
    int buffer[3];
    *out = func_0202c934(buffer, (const void *) data_020c892c, 2, param, 0x6000);
    return *out != -1;
}
