/* func_ov096_0229c4dc @ 0x0229c4dc, 0x10 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f054(void *p, unsigned char b);

struct UnkStruct_0229c4dc {
    char pad_00[0xb6];
    unsigned char b6;
};

int func_ov096_0229c4dc(struct UnkStruct_0229c4dc *p)
{
    return func_ov096_0229f054(p, p->b6);
}
