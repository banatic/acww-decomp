/* outdoor_villager_home: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226b3ac @ 0x0226b3ac, 0x6 bytes, Thumb
 * func_ov068_0226b39c @ 0x0226b39c, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[28];
    unsigned char unk_1C;
} UnkStruct_0226b3ac;

void func_ov068_0226b3ac(UnkStruct_0226b3ac *p, int event)
{
    p->unk_1C = 1;
}

void func_ov068_0226b39c(unsigned char *r0, unsigned char *r1)
{
    r1[0x561] = 0;
    r0[0x1c] = 2;
}
