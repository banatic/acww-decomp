/* func_ov115_0229e0c0 @ 0x0229e0c0, 0x28 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov115_0229de10(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov115_0229e0c0(void *self)
{
    if (func_0208e484((char *) self + 0x94)) {
        func_ov115_0229de10(self);
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0x142c));
    }
}
