/* func_020af750 @ 0x020af750, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020af028(unsigned int *);
extern unsigned int func_020af8e0(unsigned int *, unsigned int);
extern void func_020af658(unsigned int *, unsigned int);
extern void func_020af788(unsigned int *);

void func_020af750(unsigned int *ptr, unsigned int add, unsigned int other)
{
    unsigned int limit;

    limit = func_020af8e0(ptr, func_020af028(ptr));
    *ptr += add;
    if (*ptr > limit) {
        *ptr = limit;
    }
    func_020af658(ptr, other);
    func_020af788(ptr);
}
