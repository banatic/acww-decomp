/* house_looks: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b39b8 @ 0x020b39b8, 0x2 bytes, Thumb
 * func_020b39b4 @ 0x020b39b4, 0x2 bytes, Thumb
 * func_020b38dc @ 0x020b38dc, 0xd6 bytes, Thumb
 * func_020b38c0 @ 0x020b38c0, 0x1c bytes, Thumb
 * func_020b38b0 @ 0x020b38b0, 0x10 bytes, Thumb
 * func_020b38a0 @ 0x020b38a0, 0x10 bytes, Thumb
 * func_020b3880 @ 0x020b3880, 0x20 bytes, Thumb
 * func_020b3858 @ 0x020b3858, 0x28 bytes, Thumb
 * func_020b3850 @ 0x020b3850, 0x8 bytes, Thumb
 * func_020b3848 @ 0x020b3848, 0x8 bytes, Thumb
 * func_020b3830 @ 0x020b3830, 0x16 bytes, Thumb
 * func_020b3818 @ 0x020b3818, 0x18 bytes, Thumb
 * func_020b3754 @ 0x020b3754, 0xc4 bytes, Thumb
 * func_020b3750 @ 0x020b3750, 0x2 bytes, Thumb
 * func_020b374c @ 0x020b374c, 0x4 bytes, Thumb
 */

struct func_020b3858_s {
    unsigned char pad_00[0x234];
    unsigned char unk_234;
};

typedef struct Cell {
    char data[0x28];
} Cell;

typedef struct Work {
    Cell *base;
    unsigned int width;
    unsigned int height;
} Work;

typedef struct Choices_020b3750 {
    unsigned char indices[4];
} Choices_020b3750;

extern int func_020644cc(int n);
extern void *func_02072a38(void *arg);
extern int func_02072a28(int arg);
extern void func_02072998(void *ptr);
extern void func_020728f8(void *, void *);
extern void *func_02072994(void *record);
extern Work *func_0204e414(void);
extern unsigned short *func_02037e0c(Cell *, int, int, int);
extern void func_0204f800(int *, int *, unsigned int, unsigned int, int, int);
extern int func_0204e404(Work *, unsigned short *, int, int);

void func_020b39b8(void) {}

void func_020b39b4(void *object) {}

void func_020b38dc(unsigned char *arr)
{
    int idx;
    unsigned int j, i;
    unsigned int k, u, t;
    unsigned int limit, cnt, found;
    int base, val;
    int rnd1;
    unsigned int rnd2;

    rnd1 = func_020644cc(5);
    idx = 0;
    rnd2 = (unsigned int) func_020644cc(4);

    j = 0;
    i = j;
    while (i < 5) {
        if (i != (unsigned int) rnd1) {
            if (j == rnd2) {
                idx = (int) i;
                break;
            }
            j++;
        }
        i++;
    }

    for (i = 0; i < 4; i++) {
        arr[i] = 0xff;
    }

    k = 0;
    base = 5 * (rnd1 % 5);
    do {
        limit = func_020644cc(5 - k);
        cnt = 0;
        t = 0;
        while (t < 5) {
            found = 0;
            u = 0;
            val = (int) (t % 5) + base;
            while (u < 4) {
                unsigned char b = arr[u];
                if (b == val) {
                    found = 1;
                    break;
                }
                u++;
            }
            if (!found) {
                if (cnt == limit) {
                    arr[k] = val;
                    break;
                }
                cnt++;
            }
            t++;
        }
        k++;
    } while (k < 3);

    arr[3] = (unsigned char) (5 * (idx % 5) + (int) ((unsigned int) func_020644cc(5) % 5));
}

int func_020b38c0(const unsigned char *arr, int index)
{
    unsigned int val = arr[index & 3];
    if (val < 25) {
        return (int) val;
    }
    return (int) val % 25;
}

void *func_020b38b0(void *arg)
{
    func_02072a38(arg);
    return arg;
}

int func_020b38a0(int arg)
{
    func_02072a28(arg);
    return arg;
}

void func_020b3880(void *ptr)
{
    ((unsigned char *) ptr)[0x234] = func_020644cc(3);
    func_02072998(ptr);
}

int func_020b3858(struct func_020b3858_s *p)
{
    unsigned int value = p->unk_234;

    if (value >= 3) {
        p->unk_234 = value % 3;
        return func_020b3858(p);
    }
    return value;
}

void func_020b3850(void *argument0, void *argument1)
{
    func_020728f8((void *) argument0, (void *) argument1);
}

void *func_020b3848(void *record)
{
    return func_02072994(record);
}

void *func_020b3830(void *arg)
{
    func_020b39b8();
    func_020b38b0((char *) arg + 4);
    return arg;
}

void *func_020b3818(void *arg)
{
    void *p = arg;

    func_020b38a0((int) ((char *) p + 4));
    func_020b39b4(p);
    return p;
}

inline unsigned short inline_fn(unsigned short *arg0)
{
    return *arg0;
}

void func_020b3754(void *arg)
{
    unsigned int y;
    unsigned int x;
    int k;
    int j;
    Work *work;
    int flag = 1;
    int a;
    int b;
    Cell *ptr;
    unsigned short *res;
    int ok;
    func_020b38dc((unsigned char *) arg);
    func_020b3880(((char *) arg) + 4);
    work = func_0204e414();
    for (y = 1; y <= 4; y++) {
        for (x = 1; x <= 4; x++) {
            if (((x < work->width) && (y < work->height)) && work->base) {
                ptr = work->base + (x + (y * work->width));
            } else {
                ptr = 0;
            }
            if (ptr) {
                for (k = 0; k < 16; k++) {
                    for (j = 0; j < 16; j++) {
                        res = func_02037e0c(ptr, j, k, 0);
                        if (res) {
                            ok = 0;
                            if ((inline_fn(res) >= 0x5000) && (inline_fn(res) <= 0x5021)) {
                                ok = flag;
                            }
                            if (ok) {
                                func_0204f800(&a, &b, x, y, j, k);
                                func_0204e404(work, res, a, b);
                            }
                        }
                    }
                }
            }
        }
    }
}

unsigned char *func_020b3750(Choices_020b3750 *record)
{
    return record->indices;
}

int func_020b374c(int p0)
{
    return ((int) (p0) + (4));
}
