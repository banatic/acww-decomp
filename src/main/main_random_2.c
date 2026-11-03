/* main_random_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020644cc @ 0x020644cc, 0x18 bytes, ARM
 * func_020644b4 @ 0x020644b4, 0x18 bytes, ARM
 */

extern unsigned int func_020e92d0(void *arg1, int arg2);
extern unsigned char data_021cb5a0[];

unsigned int func_020644cc(int param)
{
    return func_020e92d0(((int *) data_021cb5a0), param);
}

unsigned int func_020644b4(int p)
{
    return func_020e92d0((void *) ((unsigned int) data_021cb5a0), p);
}
