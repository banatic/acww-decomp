/* func_02003330 @ 0x02003330, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003330(void *self, int a, int b, int c);

void func_02003330(void *self, int a, int b, int c)
{
    ((int *) ((char *) self + 0xb4))[0] = a;
    ((int *) ((char *) self + 0xb8))[0] = b;
    ((int *) ((char *) self + 0xbc))[0] = c;
}
