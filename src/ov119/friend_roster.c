/* friend_roster: 3 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229a420 @ 0x0229a420, 0x12 bytes, Thumb
 * func_ov119_0229a410 @ 0x0229a410, 0xe bytes, Thumb
 * func_ov119_0229a400 @ 0x0229a400, 0xe bytes, Thumb
 */

struct UnkStruct_0229a420 {
    char pad_00[0x98];
    unsigned short unk_98;
};

struct UnkStruct_0229a400 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
};

int func_ov119_0229a420(struct UnkStruct_0229a420 *obj, unsigned int mask)
{
    if ((obj->unk_98 & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov119_0229a410(unsigned short *r0, unsigned short r1)
{
    unsigned short r2;
    r2 = *(unsigned short *) ((char *) r0 + 0x98);
    r2 |= r1;
    *(unsigned short *) ((char *) r0 + 0x98) = r2;
}

void func_ov119_0229a400(struct UnkStruct_0229a400 *p, unsigned short mask)
{
    unsigned short tmp;
    tmp = p->unk_98;
    tmp &= ~mask;
    p->unk_98 = tmp;
}
