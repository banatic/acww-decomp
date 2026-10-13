/* func_020c00fc @ 0x020c00fc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020c03f4(int a, int b);
extern void func_020bec54(char *p, int n);
extern char data_021fba00[];

struct UnkStruct_020c00fc {
    unsigned char pad_00[0x60];
    unsigned int flags;
};

void func_020c00fc(struct UnkStruct_020c00fc *self)
{
    unsigned int flags;
    int y;
    int x;
    int z;
    int w;

    flags = self->flags;
    y = ((flags >> 31) & 1) != 0;
    x = (flags >> 8) & 3;
    z = func_020c03f4(x, y);
    w = z + 1;
    if (z < 15) {
        func_020bec54(data_021fba00, z);
    }
    if (w < 15) {
        func_020bec54(data_021fba00, w);
    }
}
