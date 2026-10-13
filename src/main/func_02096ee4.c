/* func_02096ee4 @ 0x02096ee4, 0x1c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern void func_02063414(void *, int, int, int, int, int, int, int, int, int);
extern int func_020644cc(int);

typedef struct {
    unsigned char pad_00[0x58];
    unsigned int unk_58;
} UnkStruct_02096ee4;

extern UnkStruct_02096ee4 data_021f39a8;

static inline unsigned short pick(unsigned int i)
{
    if (i < 5) {
        return (unsigned short) (0x1518 + i);
    }
    return 0x1518;
}

int func_02096ee4(int k)
{
    unsigned short w[4];
    int a[2];
    int b[2];

    w[0] = 0xfff1;
    switch (k) {
        case 0x23:
        case 0x32:
        case 0x5f:
        case 0x73:
            func_02063ccc(a, 2, 0);
            func_020638d4(&w[1], a, 0, 0, 1, 1, 0);
            w[0] = w[1];
            func_02063cc8(a);
            return w[0];
        case 0x4a:
            func_02063414(&w[2], 0x1380, 0x20, 0, 0, 0, 1, 0xa, 0, 1);
            w[0] = w[2];
            return w[0];
        case 0x1e:
        case 0x1f:
            func_02063ccc(b, 0, 0);
            func_020638d4(&w[3], b, 0, 0, 1, 1, 0);
            w[0] = w[3];
            func_02063cc8(b);
            return w[0];
        case 0x25:
        case 0x37:
        case 0x38:
        case 0x51: {
            unsigned short target;
            unsigned short v;
            unsigned int i;
            int n;

            target = pick(data_021f39a8.unk_58);
            n = func_020644cc(4);
            for (i = 0; i < 5; i++) {
                v = pick(i);
                if (v != target) {
                    if (n > 0) {
                        n = n - 1;
                    } else {
                        return v;
                    }
                }
            }
            return 0x1518;
        }
        case 0x2e:
            return 0x149b;
        case 0:
        case 1:
            return 0x14a4;
        case 0x6e:
        case 0x6f:
            return 0x1542;
        case 0x72:
            return 0x1518;
        case 0x48:
            return 0x3648;
        case 0x47:
            return 0x3420;
    }
    return 0xfff1;
}
