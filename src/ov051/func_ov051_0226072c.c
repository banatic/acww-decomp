/* func_ov051_0226072c @ 0x0226072c, 0x40 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(unsigned int, const char *, void *);
extern void *data_ov051_022615c0;

struct UnkStruct_0226072c {
    char pad_00[0x40];
    unsigned int unk_40;
};

void func_ov051_0226072c(struct UnkStruct_0226072c *ptr, int val)
{
    char buf[2];
    switch (val) {
        case 0:
            buf[0] = 0x31;
            func_0206844c(ptr->unk_40, buf, data_ov051_022615c0);
            break;
        case 1:
            buf[1] = 0x32;
            func_0206844c(ptr->unk_40, &buf[1], data_ov051_022615c0);
            break;
    }
}
