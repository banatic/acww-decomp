/* func_020b2b8c @ 0x020b2b8c, 0x20c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char *base;
    unsigned int w;
    unsigned int h;
} Grid;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020b2b8c;

extern Grid *func_0204e414(void);
extern int func_020b2d98(void *cell, int kind);
extern void func_020871b0(const char *s);
extern void func_02046640(int a);
extern const char data_021ebcd2[];

static inline void *cell(Grid *g, unsigned int x, unsigned int y)
{
    if (x < g->w && y < g->h && g->base != 0) {
        return g->base + (x + y * g->w) * 0x28;
    }
    return 0;
}

int func_020b2b8c(UnkStruct_020b2b8c *self, int flag)
{
    Grid *g;
    int x;
    int y;
    int i;
    int j;

    g = func_0204e414();
    if (g == 0) {
        return 0;
    }

    x = self->unk_00 >> 17;
    y = self->unk_08 >> 17;

    if (flag != 0) {
        for (i = x - 1; i >= 1; i--) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98(cell(g, i, j), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    } else {
        for (i = x + 1; i <= 4; i++) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98(cell(g, i, j), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    }

    for (i = 1; i <= 4; i++) {
        if (i != y) {
            if (func_020b2d98(cell(g, x, i), 0x5020) != 0) {
                func_020871b0(data_021ebcd2);
                func_02046640(0x44);
                return 1;
            }
        }
    }

    if (flag != 0) {
        for (i = x + 1; i <= 4; i++) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98(cell(g, i, j), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    } else {
        for (i = x - 1; i >= 1; i--) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98(cell(g, i, j), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    }

    if (func_020b2d98(cell(g, x, y), 0x5020) != 0) {
        func_020871b0(data_021ebcd2);
        func_02046640(0x44);
        return 1;
    }
    return 0;
}
