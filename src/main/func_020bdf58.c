/* func_020bdf58 @ 0x020bdf58, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct element {
    char data[20];
};

struct container {
    char pad_00[0x2f58];
    struct element array[1];
};

struct element *func_020bdf58(struct container *base, int index)
{
    return &base->array[index];
}
