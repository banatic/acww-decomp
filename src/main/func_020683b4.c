/* func_020683b4 @ 0x020683b4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x5c];
} Elem;

extern void *func_020a8bb8(Elem *elem, int value);

void func_020683b4(char *base, int index, int val1, int val2)
{
    func_020a8bb8((Elem *) ((base + 0x18ac) + 0x5c * index), val1);
    *(int *) ((base + (index << 2)) + 0x1a1c) = val2;
}
