/* func_020ee324 @ 0x020ee324, 0x9c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char unk_0E;
    unsigned char pad_0F[0x46 - 0xf];
    unsigned short unk_46;
} UnkStruct_020ee324;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short c;
    unsigned short e;
} UnkStruct_020ee324_2;

extern int data_0213e7fc;
extern int data_021fd024;
extern void func_020e8ce0(void *p, UnkStruct_020ee324_2 *dst);
extern void func_020ee8a8(void *p);

void func_020ee324(UnkStruct_020ee324 *self, unsigned short val)
{
    unsigned int cond1;

    cond1 = (self->unk_0E == 1) ? 1 : 0;
    if (cond1 != 0) {
        unsigned int cond2;

        cond2 = (data_0213e7fc == 5) ? 1 : 0;
        if (cond2 != 0) {
            self->unk_46 = val;
            return;
        }
        func_020e8ce0(&data_021fd024, (UnkStruct_020ee324_2 *) ((char *) self + 0x38));
        {
            UnkStruct_020ee324_2 *sub2 = (UnkStruct_020ee324_2 *) ((char *) self + 0x38);
            sub2->c = val;
            sub2->e = val;
        }
        func_020ee8a8(&data_021fd024);
        return;
    }

    {
        UnkStruct_020ee324_2 *sub3 = (UnkStruct_020ee324_2 *) ((char *) self + 0x38);
        sub3->c = val;
        sub3->e = val;
    }
}
