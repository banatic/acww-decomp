/* room_object_state: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d3e4 @ 0x0209d3e4, 0x14 bytes, Thumb
 * func_0209d3d0 @ 0x0209d3d0, 0x14 bytes, Thumb
 * func_0209d3bc @ 0x0209d3bc, 0x14 bytes, Thumb
 * func_0209d3a8 @ 0x0209d3a8, 0x14 bytes, Thumb
 */

struct Nibbles {
    unsigned char low : 4;
    unsigned char high : 4;
};

extern unsigned char data_021dc6cc[3];

void func_0209d3e4(void)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        data_021dc6cc[i] = 0;
    }
}

unsigned int func_0209d3d0(unsigned int x)
{
    if (x < 3) {
        return ((const unsigned char *) data_021dc6cc)[x];
    } else {
        return 0;
    }
}

int func_0209d3bc(unsigned int index, unsigned int value)
{
    if (index < 3) {
        data_021dc6cc[index] = value;
        return 1;
    } else {
        return 0;
    }
}

int func_0209d3a8(unsigned char *p)
{
    struct Nibbles *n = (struct Nibbles *) p;
    return func_0209d3bc(n->low, n->high);
}
