/* func_ov004_02246b6c @ 0x02246b6c, 0x110 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void VEC_Subtract(const void *, const void *, void *);
extern void func_0203ad68(void);
typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    Vec pos;
    int pad_0C, pad_10, value, pad_18;
    short first, second;
    int pad_20;
} Entry;
typedef struct {
    short unk_00, unk_02, unk_04, previous[2], unk_0A, unk_0C;
    unsigned char unk_0E;
} State;
Entry data_ov004_022569ec[];

#define WORD(o) (*(int *) ((char *) self + (o)))
#define HALF(o) (*(short *) ((char *) self + (o)))
void func_ov004_02246b6c(void *self)
{
    State *b = (State *) ((char *) self + 0x21c);
    int excluded[2];
    int i;
    Entry *entry;
    b->unk_00 = 0;
    if (func_020644cc(2) == 1) {
        b->unk_02 = func_020644cc(b->unk_0C - 2);
    } else {
        b->unk_02 = func_020644cc(b->unk_0C);
    }
    if (b->previous[0] > b->previous[1]) {
        excluded[0] = b->previous[1];
        excluded[1] = b->previous[0];
    } else {
        excluded[0] = b->previous[0];
        excluded[1] = b->previous[1];
    }
    for (i = 0; i < 2; ++i) {
        if (excluded[i] != -1 && (b->unk_02 >> 1) >= (excluded[i] >> 1)) {
            b->unk_02 += 2;
        }
    }
    if (b->previous[b->unk_0A] == -1) {
        b->unk_0C -= 2;
    }
    b->previous[b->unk_0A] = b->unk_02;
    b->unk_0A ^= 1;
    b->unk_04 = 1;
    entry = &data_ov004_022569ec[b->unk_02];
    WORD(0x110) = entry->pos.x;
    WORD(0x114) = entry->pos.y;
    WORD(0x118) = entry->pos.z;
    VEC_Subtract((char *) self + 0x110, (char *) self + 0x104, (char *) self + 0x110);
    HALF(0xfe) = entry->second;
    HALF(0xfc) = entry->first;
    WORD(0x100) = entry->value;
    func_0203ad68();
}
