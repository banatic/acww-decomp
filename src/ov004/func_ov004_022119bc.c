/* func_ov004_022119bc @ 0x022119bc, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Fn)(void *self, int a, int b);

void func_ov004_022119bc(void *self)
{
    (*(Fn **) self)[28](self, 2, 0xff);
}
