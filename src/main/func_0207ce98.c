/* func_0207ce98 @ 0x0207ce98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Elem {
    char data[0x7ec];
};

extern int func_0207cf14(void *, void *);
extern int func_0207cf74(unsigned int);

struct Elem *func_0207ce98(struct Elem *base, void *argument1)
{
    struct Elem *result = 0;
    int index = func_0207cf14((void *) base, (void *) argument1);
    if (func_0207cf74(index) != 0) {
        result = base + index;
    }
    return result;
}
