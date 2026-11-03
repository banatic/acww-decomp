/* gull_spots: 2 functions, module ov072
 * mwccarm 1.2/base -O1,s
 * func_ov072_022791b0 @ 0x022791b0, 0x134 bytes, Thumb
 * func_ov072_02279098 @ 0x02279098, 0x118 bytes, Thumb
 */

typedef struct Cell {
    char data[0x28];
} Cell;

typedef struct Work {
    Cell *base;
    unsigned int width;
    unsigned int height;
} Work;

extern int func_020644cc(int);
extern unsigned short *func_02037e0c(Cell *, int, int, int);
extern int func_0204ee48(Work *, int, int, int, int);
extern int func_ov072_022792e4(int *, int *, Work *);
extern int func_02037e44(Cell *, unsigned short *, int, int, int);
extern Work *func_0204e414(void);
extern void MI_CpuFill8(void *dst, int val, int len);

inline Cell *getcell(Work *work, int x, int y)
{
    if (x < work->width && y < work->height && work->base != 0) {
        return work->base + (y * work->width + x);
    }
    return 0;
}

int func_ov072_022791b0(unsigned char *p, int *cnt, Work *work)
{
    int v1;
    unsigned short *ent;
    int v2;
    Cell *cell;
    unsigned short hw;
    int xy[2];
    int jk[2];

    v1 = func_020644cc(*cnt);
    xy[0] = 0;
    xy[1] = 0;
    jk[0] = 0;
    jk[1] = 0;
    for (xy[1] = 1; xy[1] < 5; xy[1]++) {
        for (xy[0] = 1; xy[0] < 5; xy[0]++) {
            if (*p != 0) {
                if (v1 == 0) {
                    cell = getcell(work, xy[0], xy[1]);
                    if (cell != 0) {
                        ent = func_02037e0c(cell, 0, 0, 0);
                        if (ent != 0) {
                            v2 = func_020644cc(*p);
                            for (jk[1] = 0; jk[1] < 16; jk[1]++) {
                                for (jk[0] = 0; jk[0] < 16; ent++, jk[0]++) {
                                    if (*ent != 0xfff1) {
                                        continue;
                                    }
                                    if (func_0204ee48(work, xy[0], xy[1], jk[0], jk[1]) == 0) {
                                        continue;
                                    }
                                    if (func_ov072_022792e4(xy, jk, work) == 0) {
                                        continue;
                                    }
                                    if (v2 == 0) {
                                        hw = 0x1568;
                                        func_02037e44(cell, &hw, jk[0], jk[1], 0);
                                        (*p)--;
                                        if (*p == 0) {
                                            (*cnt)--;
                                        }
                                        return 1;
                                    }
                                    v2--;
                                }
                            }
                        }
                    }
                }
                v1--;
            }
            p++;
        }
    }
    return 0;
}

void func_ov072_02279098(void)
{
    Work *work;
    int total;
    unsigned char *p;
    unsigned short *ent;
    Cell *cell;
    int i;
    int xy[2];
    int jk[2];
    int cnt;
    unsigned char counts[16];

    work = func_0204e414();
    if (work == 0) {
        return;
    }

    total = 0;
    xy[0] = 0;
    xy[1] = 0;
    jk[0] = 0;
    jk[1] = 0;
    cnt = 0;
    p = counts;
    MI_CpuFill8(p, 0, 0x10);

    for (xy[1] = 1; xy[1] < 5; xy[1]++) {
        for (xy[0] = 1; xy[0] < 5; p++, xy[0]++) {
            cell = getcell(work, xy[0], xy[1]);
            if (cell == 0) {
                continue;
            }
            ent = func_02037e0c(cell, 0, 0, 0);
            if (ent == 0) {
                continue;
            }
            for (jk[1] = 0; jk[1] < 16; jk[1]++) {
                for (jk[0] = 0; jk[0] < 16; ent++, jk[0]++) {
                    if (*ent != 0xfff1) {
                        continue;
                    }
                    if (func_0204ee48(work, xy[0], xy[1], jk[0], jk[1]) == 0) {
                        continue;
                    }
                    if (func_ov072_022792e4(xy, jk, work) == 0) {
                        continue;
                    }
                    (*p)++;
                }
            }
            if (*p != 0) {
                total += *p;
                cnt++;
            }
        }
    }

    if (total >= 5) {
        total = 5;
    }

    for (i = 0; i < total; i++) {
        func_ov072_022791b0(counts, &cnt, work);
        if (cnt <= 0) {
            return;
        }
    }
}
