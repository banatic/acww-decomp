/* func_0209765c @ 0x0209765c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020d18e0[];
extern void *data_020e3058[];
extern int func_020644cc(void *ptr);

unsigned char func_0209765c(int index)
{
    void *ptr;
    int val;
    unsigned char *base;

    ptr = data_020d18e0[index];
    val = func_020644cc(ptr);
    base = (unsigned char *) data_020e3058[index];
    return base[val];
}
