/* func_020360a8 @ 0x020360a8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020360a8 {
    unsigned char pad_00[0x10];
    unsigned char flag;
    unsigned char pad1[0x1c0 - 0x11];
    int count;
};

struct Block {
    unsigned char pad_00;
    unsigned char val;
    unsigned char pad1[0xe];
};

struct UnkStruct_020360a8_2 {
    struct UnkStruct_020360a8 *inner;
    unsigned char pad_04[0x20];
    struct Block blocks[5];
};

void func_020360a8(struct UnkStruct_020360a8_2 *p)
{
    struct Block *b;
    struct Block *end;
    char one;

    if (p->inner->count <= 0) {
        return;
    }
    if (p->inner->flag == 0) {
        return;
    }

    b = p->blocks;
    end = (struct Block *) ((char *) p + 0x74);
    one = 1;
    while (b < end) {
        b->val = one;
        b++;
    }
}
