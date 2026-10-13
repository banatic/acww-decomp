/* func_020f9848 @ 0x020f9848, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213f25c;
extern int data_021fd1bc;

unsigned int *func_020f9848(unsigned int *out)
{
    *out = (unsigned int) &data_0213f25c;
    data_021fd1bc = 0;
    return out;
}
