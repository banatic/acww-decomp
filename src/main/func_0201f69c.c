/* func_0201f69c @ 0x0201f69c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x100];
    char *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0201f69c;

typedef struct {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_0201f69c_2;

extern int func_0203fdc4(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_0201f69c *, char *, unsigned char *, int, int, int, int, int, int);
extern int data_020c8bd8;

void func_0201f69c(UnkStruct_0201f69c *base, UnkStruct_0201f69c_2 *out)
{
    int val, r4, r6, a5, a6, a7, a8, a9;

    val = func_0203fdc4(14);
    if (val < 0) {
        val = 0;
    }

    if (val == 0) {
        r4 = 2;
        r6 = 0;
    } else if (val >= 1 && val <= 2) {
        r4 = 3;
        r6 = 2;
    } else if (val >= 3 && val <= 5) {
        r4 = 3;
        r6 = 5;
    } else {
        r4 = 2;
        r6 = 8;
    }

    a5 = func_020036e8(func_0208150c(*(int *) (base->ptr + 0x830)));
    a6 = data_020c8bd8;
    a7 = 1;
    a8 = r6;
    a9 = (unsigned char) r4;

    func_0202da38(base, base->unk_104, &base->unk_122, 30, a5, a6, a7, a8, a9);

    out->unk_00 = base->unk_104;
    out->unk_04 = base->unk_122;
}
