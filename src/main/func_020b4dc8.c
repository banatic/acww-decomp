/* func_020b4dc8 @ 0x020b4dc8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4dc8 {
    int pad_00;
    int value;
    unsigned char x;
    unsigned char y;
};

struct UnkStruct_020b4dc8_2 {
    char pad_00[0x24];
    struct UnkStruct_020b4dc8 *data;
};

extern void func_020a86e4(void *p, unsigned char *b0, unsigned char *b1, unsigned char *b2);

void func_020b4dc8(struct UnkStruct_020b4dc8_2 *p)
{
    unsigned char b[3];
    struct UnkStruct_020b4dc8 *dst;
    unsigned int v;

    func_020a86e4((char *) p + 0x28, &b[0], &b[1], &b[2]);
    dst = (struct UnkStruct_020b4dc8 *) ((char *) p->data + 0xaf0);
    v = b[0];
    if (v < 3) {
        // nothing
    } else {
        v = -1;
    }
    dst->value = (int) v;
    dst->x = b[1];
    dst->y = b[2];
}
