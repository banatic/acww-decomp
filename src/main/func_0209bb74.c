/* func_0209bb74 @ 0x0209bb74, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct0209bb74 {
    unsigned char pad_00[11];
    unsigned char unk_0B;
};

void func_0209bb74(struct UnkStruct0209bb74 *r0, unsigned int r1)
{
    r0->unk_0B = (r0->unk_0B & ~0xe0U) | ((r1 & 7U) << 5);
}
