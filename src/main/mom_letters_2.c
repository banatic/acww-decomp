/* mom_letters_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209767c @ 0x0209767c, 0x28 bytes, Thumb
 * func_0209765c @ 0x0209765c, 0x20 bytes, Thumb
 * func_0209761c @ 0x0209761c, 0x40 bytes, Thumb
 */

extern int func_020644cc(int arg);
extern void *data_020d18e0[];
extern void *data_020e3058[];
extern int data_020d18d0[];
extern unsigned char *data_020e3048[];

unsigned char func_0209765c(int index);
unsigned char func_0209761c(unsigned int param);

int func_0209767c(int p1, int p2)
{
    if (func_020644cc(10) < 3) {
        return (int) func_0209761c(p2);
    } else {
        return (int) func_0209765c(p1);
    }
}

unsigned char func_0209765c(int index)
{
    void *ptr;
    int val;
    unsigned char *base;

    ptr = data_020d18e0[index];
    val = func_020644cc((int) ptr);
    base = (unsigned char *) data_020e3058[index];
    return base[val];
}

unsigned char func_0209761c(unsigned int param)
{
    unsigned int index;
    if (param <= 2 || param == 12) {
        index = 3;
    } else if (param <= 5) {
        index = 0;
    } else if (param <= 8) {
        index = 1;
    } else {
        index = 2;
    }
    return data_020e3048[index][func_020644cc(data_020d18d0[index])];
}
