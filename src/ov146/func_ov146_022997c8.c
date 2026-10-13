/* func_ov146_022997c8 @ 0x022997c8, 0x24 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[36];
} Element36;

typedef struct {
    char pad_00[0x1ea0];
    Element36 arr[2];
} Parent;

extern void func_020b9ccc(Element36 *);

void func_ov146_022997c8(Parent *p)
{
    int i;
    for (i = 0; i < 2; i++) {
        func_020b9ccc(&p->arr[i]);
    }
}
