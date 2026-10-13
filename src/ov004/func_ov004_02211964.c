/* func_ov004_02211964 @ 0x02211964, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Fn)(void *self, int a, int b);

void func_ov004_02211964(void *self)
{
    (*(Fn **) self)[28](self, 0, 0xff);
}
