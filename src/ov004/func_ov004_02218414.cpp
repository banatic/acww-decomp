/* func_ov004_02218414 @ 0x02218414, 0x134 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Cell;
extern "C" void func_ov004_022183b8(char *, int *, int *, int, int *);
extern "C" void func_0204f818(int *, int *, int *);
extern "C" void *func_ov004_0223cd50(void);
extern "C" char *func_ov004_0223cc10(void *, int, int, int);
extern "C" int func_ov004_0220fe24(int *, int, int, int, int);
extern "C" int func_ov004_0220fde0(char *);
extern "C" int func_020538dc(int);
extern "C" void *func_ov004_02218364(Cell *);
extern "C" void *func_ov004_02218354(Cell *);
extern "C" unsigned int func_ov004_02218548(char *, Cell *);
extern "C" Cell *func_ov004_02218394(Cell *, unsigned int);
extern "C" int func_ov004_0223c5a4(int *);
extern "C" int func_02030890(int *);
static inline int pair_type(char *p)
{
    if (*(unsigned short *) (p + 12) == 0x37) {
        return 1;
    }
    return 0;
}
extern "C" int func_ov004_02218414(char *self, int *position, int angle, int *offset)
{
    int x, y;
    int moved[3];
    Cell a[2], b[2];
    char *other;
    unsigned int countA, countB, i, j;
    func_ov004_022183b8(self, moved, position, angle, offset);
    func_0204f818(&x, &y, moved);
    other = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
    if (!func_ov004_0220fe24(moved, 0x800, 0x2000, 0x800, 0)) {
        return 0;
    }
    if (other) {
        if (other == self) {
            return 1;
        }
        if (func_020538dc(func_ov004_0220fde0(other))) {
            return 2;
        }
        if (*(short *) (self + 0x8e) == *(short *) (other + 0x8e) && pair_type(other)) {
            func_ov004_02218364(a);
            func_ov004_02218364(b);
            countA = func_ov004_02218548(self, a);
            countB = func_ov004_02218548(other, b);
            for (i = 0; i < countA; ++i) {
                Cell *p = func_ov004_02218394(a, i);
                int ax = p->x, ay = p->y;
                for (j = 0; j < countB; ++j) {
                    Cell *q = func_ov004_02218394(b, j);
                    int by = q->y, bx = q->x;
                    bx = ax - bx;
                    if (bx < 0) {
                        bx = -bx;
                    }
                    by = ay - by;
                    if (by < 0) {
                        by = -by;
                    }
                    if (bx + by == 1) {
                        func_ov004_02218354(b);
                        func_ov004_02218354(a);
                        return 1;
                    }
                }
            }
            func_ov004_02218354(b);
            func_ov004_02218354(a);
        }
    } else if (!func_ov004_0223c5a4(moved) && func_02030890(moved) == -1) {
        return 2;
    }
    return 0;
}
