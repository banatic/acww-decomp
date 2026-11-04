/* sound_slots_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020efa3c @ 0x020efa3c, 0x30 bytes, ARM
 * func_020efa30 @ 0x020efa30, 0xc bytes, ARM
 */

struct UnkStruct_020efa30 {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[4];
    unsigned char unk_0A;
};

extern void func_0210b7e0(void *);

void func_020efa3c(void *p)
{
    func_0210b7e0(p);
    ((unsigned char *) p)[8] = 0;
    ((unsigned short *) ((char *) p + 6))[0] = 0;
    ((unsigned char *) p)[9] = 0;
    ((unsigned short *) ((char *) p + 4))[0] = 0;
    ((unsigned char *) p)[10] = 0x7f;
}

void func_020efa30(struct UnkStruct_020efa30 *p, unsigned char b, unsigned short h)
{
    p->unk_0A = b;
    p->unk_04 = h;
}
