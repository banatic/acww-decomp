/* func_02094c8c @ 0x02094c8c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xE];
    short unk_0E;
    char pad_10[0x4];
    int unk_14;
    char pad_18[0x4];
} Entry;

extern Entry data_021d52d8[];
extern void func_020914dc(Entry *);

typedef struct {
    unsigned char b[4];
} Key;

int func_02094c8c(unsigned char *param)
{
    Key tmp;
    Entry *e;
    int flag;

    tmp = *(Key *) (param + 4);
    e = &data_021d52d8[tmp.b[0]];
    flag = 0;
    if (e->unk_14 != -1) {
        if (e->unk_0E != 0) {
            if (e->unk_0E > 0) {
                e->unk_0E--;
            }
            flag = 1;
        }
    }

    if (flag == 0) {
        func_020914dc(e);
    }
    return flag;
}
