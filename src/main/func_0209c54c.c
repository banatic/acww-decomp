/* func_0209c54c @ 0x0209c54c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1a94[];
extern char data_020d1a90[];
extern int func_020644cc(int);

int func_0209c54c(int *out, int idx)
{
    int off = idx * 8;
    *out = func_020644cc(data_020d1a94[off]);
    return *(int *) (data_020d1a90 + off);
}
