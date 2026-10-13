/* func_ov068_0226ec54 @ 0x0226ec54, 0x54 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbee8[3];

struct UnkStruct_0226ec54 {
    unsigned char pad_00[0x308];
    int vec[3];
    unsigned char pad_314[0x64];
    unsigned short flags;
    unsigned char pad_37A[0x1c];
    unsigned short half;
    unsigned char byte;
};

int func_ov068_0226ec54(struct UnkStruct_0226ec54 *p)
{
    p->flags &= ~0x10;
    p->flags |= 0x20;
    p->vec[0] = data_021fbee8[0];
    p->vec[1] = data_021fbee8[1];
    p->vec[2] = data_021fbee8[2];
    p->half = 0;
    p->byte = 0xc;
    return 1;
}
