/* func_0206e4fc @ 0x0206e4fc, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned int uintptr_t;

extern int func_020e98f4(int, int);

void *func_0206e4fc(int name, unsigned int size, int align)
{
    (void) name;
    return (void *) (uintptr_t) (unsigned int) func_020e98f4(size, align);
}
