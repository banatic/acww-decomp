/* func_02092f00 @ 0x02092f00, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094bcc(int a, int b, void *c);
extern int data_020d1768;

int func_02092f00(int a)
{
    return func_02094bcc(a, 0, &data_020d1768);
}
