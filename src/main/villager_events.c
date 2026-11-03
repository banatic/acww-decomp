/* villager_events: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020797bc @ 0x020797bc, 0xe4 bytes, Thumb
 * func_02079798 @ 0x02079798, 0x24 bytes, Thumb
 * func_02079774 @ 0x02079774, 0x24 bytes, Thumb
 * func_02079750 @ 0x02079750, 0x24 bytes, Thumb
 * func_0207972c @ 0x0207972c, 0x24 bytes, Thumb
 * func_02079708 @ 0x02079708, 0x24 bytes, Thumb
 * func_020796e4 @ 0x020796e4, 0x24 bytes, Thumb
 * func_02079690 @ 0x02079690, 0x54 bytes, Thumb
 * func_02079664 @ 0x02079664, 0x2c bytes, Thumb
 * func_02079640 @ 0x02079640, 0x24 bytes, Thumb
 * func_020795f4 @ 0x020795f4, 0x4c bytes, Thumb
 */

#define G ((void *) 0x021e5a2c)

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Box;

typedef struct {
    char pad_00[0x168];
    int unk_168;
} Res;

typedef struct {
    unsigned char *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Map;

extern void func_0209e474(void *p);
extern void *func_0207cec0(void *g, int i);
extern int func_0208150c(void *e);
extern int func_02003704(int x);
extern int func_0207f1c8(void *e);
extern int func_0209b5ec(void *);
extern int func_0209c1c0(int x, void *buf);
extern int func_020798a0(unsigned short *h, int x0, int x1, int x2, int x3);
extern void func_0207dac8(void *e, int a, int mode);
extern Res *func_02079350(void);
extern int func_02073d90(int arg);
extern int data_020ccf94;
extern Map *data_021c80bc;
extern int func_02037d80(unsigned char *cell, int k);
extern int func_020b6660(void);

void func_020797bc(int a, Box *b)
{
    void *e;
    int x3;
    int x0;
    unsigned short h;
    int i;
    int x1;
    int x2;
    int buf[2];
    int mode;

    if (G != 0) {
        x0 = 0;
        buf[0] = 0;
        buf[1] = 0;
        x1 = 0;
        x2 = 0;
        x3 = 0;
        h = 0xfff1;
        if (b != 0) {
            x0 = b->unk_00 - 0x10000;
            x1 = b->unk_00 + 0x10000;
            x2 = b->unk_08 - 0x1a000;
            x3 = b->unk_08 + 0xa000;
        }
        func_0209e474(buf);
        for (i = 0; i < 8; i++) {
            mode = 1;
            e = func_0207cec0(G, i);
            if (e != 0) {
                if (func_02003704(func_0208150c(e))) {
                    if (func_0209c1c0((func_0209b5ec((void *) func_0207f1c8(e))), buf)) {
                        if (b != 0) {
                            h = (unsigned short) ((i & 0xfff) | 0xe000);
                            if (func_020798a0(&h, x0, x1, x2, x3)) {
                                mode = 2;
                            }
                        }
                        func_0207dac8(e, a, mode);
                    }
                }
            }
        }
        func_02079350()->unk_168 = 0;
    }
}

void func_02079798(int param)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_020797bc(1, (Box *) param);
    }
}

void func_02079774(void *param)
{
    int result;

    result = func_02073d90((int) ((*(void * *) &data_020ccf94)));
    if (result == 0) {
        func_020797bc(0, (Box *) param);
    }
}

void func_02079750(int param)
{
    int ret;

    ret = func_02073d90(data_020ccf94);
    if (ret != 0) {
        return;
    }
    func_020797bc(2, (Box *) param);
}

void func_0207972c(void)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_020797bc(3, 0);
    }
}

void func_02079708(void)
{
    if (func_02073d90((*(unsigned int *) &data_020ccf94)) == 0) {
        func_020797bc(4, 0);
    }
}

void func_020796e4(int arg0)
{
    int ret = func_02073d90(data_020ccf94);
    if (ret != 0) {
        return;
    }
    func_020797bc(5, (Box *) arg0);
}

int func_02079690(int *p)
{
    Map *m = data_021c80bc;
    if (m != 0) {
        unsigned char *cell;
        unsigned int y = (unsigned int) (p[2] >> 17);
        unsigned int x = (unsigned int) (p[0] >> 17);
        if (x < m->unk_04 && y < m->unk_08 && m->unk_00 != 0) {
            cell = m->unk_00 + (x + y * m->unk_04) * 0x28;
        } else {
            cell = 0;
        }
        if (cell != 0 && func_02037d80(cell, 8) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_02079664(int param)
{
    if (func_02073d90(data_020ccf94) == 0) {
        if (func_02079690((int *) param) != 0) {
            func_020797bc(6, (Box *) param);
        }
    }
}

void func_02079640(void)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_020797bc(7, 0);
    }
}

void func_020795f4(void)
{
    if (func_020b6660() == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    {
        int *p = (int *) func_02079350();
        if ((unsigned) p[0x5A] > 0x4b0u) {
            func_02079640();
        }
        p = (int *) func_02079350();
        p[0x5A]++;
    }
}
