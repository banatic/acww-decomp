/* func_0207ce98 @ 0x0207ce98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Elem {
    char data[0x7ec];
};

extern int func_0207cf14(void);
extern int func_0207cf74(void);

struct Elem *func_0207ce98(struct Elem *base)
{
    struct Elem *result = 0;
    int index = func_0207cf14();
    if (func_0207cf74() != 0) {
        result = base + index;
    }
    return result;
}
