/* func_02074fec @ 0x02074fec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073364(void *ptr);
extern int func_0207500c(int a, int b);

int func_02074fec(int a)
{
    return func_0207500c(a, func_02073364(data_020ccf94));
}
