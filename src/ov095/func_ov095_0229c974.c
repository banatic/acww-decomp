/* func_ov095_0229c974 @ 0x0229c974, 0xf0 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c974 {
    int unk_00;
    unsigned int lo : 12;
    unsigned int pal : 4;
    unsigned int hi : 16;
} UnkStruct_0229c974;

extern int func_ov095_0229c930(void *a, int unused1, int unused2);
extern UnkStruct_0229c974 *func_ov095_0229b16c(void *a);

void func_ov095_0229c974(void *a, int id, int val)
{
    UnkStruct_0229c974 *p;
    int idx;
    int i;

    if (func_ov095_0229c930(a, id, val) != 0) {
        return;
    }
    if (id < 0xc9 || id > 0xf6) {
        return;
    }
    p = func_ov095_0229b16c(a);
    idx = -1;
    if (id <= 0xd2) {
        idx = id - 0xc9;
    } else if (id <= 0xdc) {
        idx = id - 0xc9;
    } else if (id == 0xdd) {
        p[0x14].pal = val;
        p[0x15].pal = val;
        return;
    } else if (id <= 0xe6) {
        idx = id - 0xc8;
    } else if (id == 0xe7) {
        for (i = 0x1f; i <= 0x21; i++) {
            p[i].pal = val;
        }
        return;
    } else if (id <= 0xf1) {
        idx = id - 0xc6;
    } else if (id == 0xf4) {
        for (i = 0x2e; i <= 0x31; i++) {
            p[i].pal = val;
        }
        return;
    } else if (id <= 0xf3) {
        idx = id - 0xc6;
    } else if (id <= 0xf6) {
        idx = id - 0xc3;
    }
    if (idx < 0) {
        return;
    }
    p[idx].pal = val;
}
