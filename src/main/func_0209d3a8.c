/* func_0209d3a8 @ 0x0209d3a8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d3bc(int a, int b);

struct Nibbles {
    unsigned char low : 4;
    unsigned char high : 4;
};

int func_0209d3a8(unsigned char *p)
{
    struct Nibbles *n = (struct Nibbles *) p;
    return func_0209d3bc(n->low, n->high);
}
