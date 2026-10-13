/* func_ov102_0229d258 @ 0x0229d258, 0x1c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    char pad_00[0x25aa];
    unsigned char index;
};

void *func_ov102_0229d258(struct Node *n)
{
    return (char *) n + 0x24e8 + ((15 * n->index) << 1);
}
