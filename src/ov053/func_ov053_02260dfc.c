/* func_ov053_02260dfc @ 0x02260dfc, 0x124 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *ptr);
extern int func_02019de8(void *ptr);
extern void func_0201b044(void *dst, void *src);
extern void func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_ov053_02261524(void *p, int n);

typedef struct {
    int unk_00;
    int w1;
    int w2;
} Entry;

extern Entry data_ov053_022617fc[];
extern Entry data_ov053_02261804[];
extern volatile unsigned short data_020c80f8;

typedef struct {
    unsigned char pad_00[0x350];
    int unk_350;
    unsigned char pad_354[0x214 - 4];
    int unk_564;
    unsigned char pad_568[0x1b5 - 4];
    unsigned char unk_719;
} UnkStruct_02260dfc;

int func_ov053_02260dfc(UnkStruct_02260dfc *p)
{
    int tmp[3];
    Entry *e;
    unsigned short val;

    if (func_02019e00((char *) p + 0x564) == 6) {
        e = &data_ov053_022617fc[p->unk_719];
        tmp[0] = e->unk_00;
        tmp[1] = e->w1;
        tmp[2] = e->w2;
        func_0201b044((char *) p + 0x350, tmp);
        if (func_02019de8((char *) p + 0x564)) {
            p->unk_719++;
            val = data_020c80f8;
            func_02019d0c((char *) p + 0x564, 6, 1, data_ov053_022617fc[p->unk_719].unk_00,
                          data_ov053_02261804[p->unk_719].unk_00, 0x800, 0, 0, 0, data_020c80f8, 0);
            if (p->unk_719 >= 2) {
                func_02019d0c((char *) p + 0x564, 3, 1, 0, 0, 0, 0xffffc000, 0, 0, val, 0);
            }
        }
    }

    if (func_02019e00((char *) p + 0x564) == 3) {
        if (func_02019de8((char *) p + 0x564)) {
            if (p->unk_719 >= 2) {
                func_ov053_02261524(p, 8);
            } else {
                func_02019d0c((char *) p + 0x564, 6, 1, data_ov053_022617fc[p->unk_719].unk_00,
                              data_ov053_02261804[p->unk_719].unk_00, 0x800, 0, 0, 0, data_020c80f8, 0);
            }
        }
    }

    return 1;
}
