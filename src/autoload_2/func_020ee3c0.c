/* func_020ee3c0 @ 0x020ee3c0, 0x9c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char unk_0E;
    unsigned char pad_0F[0x36 - 0xf];
    unsigned short unk_36;
} UnkStruct_020ee3c0;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short c;
    unsigned short e;
} UnkStruct_020ee3c0_2;

extern int data_0213e7fc;
extern int data_021fd004;
extern int func_020e8ce0(void *p, UnkStruct_020ee3c0_2 *dst);
extern int func_020ee8a8(void *p, void *node);

void func_020ee3c0(UnkStruct_020ee3c0 *self, unsigned short val)
{
    unsigned int cond1;

    cond1 = (self->unk_0E == 1) ? 1 : 0;
    if (cond1 != 0) {
        unsigned int cond2;

        cond2 = (data_0213e7fc == 3) ? 1 : 0;
        if (cond2 != 0) {
            self->unk_36 = val;
            return;
        }
        func_020e8ce0(&data_021fd004, (UnkStruct_020ee3c0_2 *) ((char *) self + 0x28));
        {
            UnkStruct_020ee3c0_2 *sub2 = (UnkStruct_020ee3c0_2 *) ((char *) self + 0x28);
            sub2->c = val;
            sub2->e = val;
        }
        func_020ee8a8(&data_021fd004, (char *) self + 0x28);
        return;
    }

    {
        UnkStruct_020ee3c0_2 *sub3 = (UnkStruct_020ee3c0_2 *) ((char *) self + 0x28);
        sub3->c = val;
        sub3->e = val;
    }
}
