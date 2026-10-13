/* func_ov068_0226d728 @ 0x0226d728, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e1a0(void *);
extern void func_02012280(void *);
extern void func_0209129c(unsigned int);

int func_ov068_0226d728(void *p)
{
    void *self;

    self = p;
    if (func_0202e1a0(p) == 0) {
        return 0;
    }
    func_02012280((char *) self + 0x9b4);
    *(unsigned int *) ((char *) self + 0x628) = 0;
    if (*(unsigned int *) ((char *) self + 0xa00) != (unsigned int) -1) {
        func_0209129c(*(unsigned int *) ((char *) self + 0xa00));
        *(unsigned int *) ((char *) self + 0xa00) = (unsigned int) -1;
    }
    return 1;
}
