/* func_02085d6c @ 0x02085d6c, 0xaa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x50];
    char grid[4];
} UnkStruct_02085d6c;

extern int func_02084e90(void *);
extern void func_02084e40(void *, int, int);
extern int func_02084e20(void *, int, int);
extern int func_020644cc(int);
extern void func_0204f794(void *, int, int);

int func_02085d6c(UnkStruct_02085d6c *o, void *p)
{
    int n, x, y, r, i, j;

    if (func_02084e90(&o->grid) != 0) {
        n = 0;
        for (x = 0; x < 0x10; x++) {
            func_02084e40(&o->grid, x, 0xe);
            func_02084e40(&o->grid, x, 0xf);
        }
        for (y = 0; y < 0xe; y++) {
            for (x = 0; x < 0x10; x++) {
                if (func_02084e20(&o->grid, x, y) != 0) {
                    n++;
                }
            }
        }
        if (n > 0) {
            r = func_020644cc(n);
            for (i = 0; i < 0xe; i++) {
                for (j = 0; j < 0x10; j++) {
                    if (func_02084e20(&o->grid, j, i) != 0) {
                        if (r == 0) {
                            func_0204f794(p, j, i);
                            return 1;
                        }
                        r--;
                    }
                }
            }
        }
    }
    return 0;
}
