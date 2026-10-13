/* func_02088ad4 @ 0x02088ad4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char lo : 2;
    unsigned char val : 4;
    unsigned char hi : 2;
} Bits;

typedef struct {
    unsigned char pad_00[0x10];
    Bits bits;
} UnkStruct_02088ad4;

void func_02088ad4(UnkStruct_02088ad4 *p)
{
    Bits *b = &p->bits;
    p->bits.val = p->bits.val + 1;
    if ((unsigned int) p->bits.val > 0xA) {
        b->val = 0xA;
    }
}
