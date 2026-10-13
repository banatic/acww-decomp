/* func_02082740 @ 0x02082740, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *ptr;
    int pad_04;
} Elem;

extern int func_020828c0(void *base, Elem *elem);
extern void func_0204f818(int *a, int *b, void *data);

void *func_02082740(void *base, int param1, int param2)
{
    Elem *elem;
    int i;
    int a, b;
    void *result = 0;

    elem = (Elem *) ((char *) base + 0x40);
    a = 0;
    b = 0;
    for (i = 0; i < 4; i++) {
        if (func_020828c0(base, elem)) {
            func_0204f818(&a, &b, (char *) elem->ptr + 0x5c);
            if (a == param1 && b == param2) {
                result = elem->ptr;
                break;
            }
        }
        elem = (Elem *) ((char *) elem + 8);
    }
    return result;
}
