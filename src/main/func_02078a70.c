/* func_02078a70 @ 0x02078a70, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02078c2c(void *);
extern int func_020e9b9c(void *);

extern unsigned char data_021d1310[];

int func_02078a70(int *out, int value)
{
    int result = func_020e9b9c(func_02078c2c((void *) data_021d1310));
    *out = value;
    return result;
}
