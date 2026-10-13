/* func_020953c4 @ 0x020953c4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct _020953c4_struct {
    unsigned char pad_00[0x804];
    unsigned int value;
};
extern struct _020953c4_struct *func_02096718(int arg);

void func_020953c4(unsigned int *ptr)
{
    struct _020953c4_struct *res;
    res = func_02096718(4);
    if (res != 0) {
        res->value = *ptr;
    }
}
