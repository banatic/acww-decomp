/* func_ov003_0220eb8c @ 0x0220eb8c, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x7d8 - 0x2d0 - 1];
    unsigned char unk_7D8;
    char pad_7D9[0x7f0 - 0x7d8 - 1];
    void *unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
    char pad_800[0x8e8 - 0x7fc - 4];
    unsigned char unk_8E8;
} UnkStruct_0220eb8c;

extern int func_02056f94(char *);
extern int func_02008258(UnkStruct_0220eb8c *, void *);
extern int func_0200d4e8(UnkStruct_0220eb8c *, int, int, int);

void func_ov003_0220eb8c(UnkStruct_0220eb8c *obj)
{
    if (obj->unk_7D8 == 1) {
        if (func_02056f94(&obj->unk_2D0) != 0) {
            obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
            func_0200d4e8(obj, 3, 1, -1);
            obj->unk_8E8 = 60;
        }
    }
}
