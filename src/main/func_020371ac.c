/* func_020371ac @ 0x020371ac, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int p1, int p2, int p3);

struct func_020371ac_data {
    unsigned char pad_00[0xe];
    unsigned char flag;
};

void func_020371ac(struct func_020371ac_data *self, int arg2)
{
    if (self->flag == 0) {
        func_02035684(0x1b, arg2, 0);
        self->flag = 1;
    }
}
