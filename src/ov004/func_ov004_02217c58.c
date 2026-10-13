/* func_ov004_02217c58 @ 0x02217c58, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Fn)(void *self, int a, int b);

void func_ov004_02217c58(void *self)
{
    (*(Fn **) self)[28](self, 8, 0xff);
}
