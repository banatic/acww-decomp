/* func_0205f910 @ 0x0205f910, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f958(void);
extern int func_020e9968(int *p, int val, int n);
extern int *data_021c9ae0;
extern unsigned char *data_020ccf94;

void func_0205f910(int *out)
{
    int *p = data_021c9ae0;
    unsigned int count = data_020ccf94[0x6c];
    unsigned int i;

    for (i = 0; i < count; i++) {
        out[i] = func_020e9968(p, func_0205f958(), 4);
    }
}
