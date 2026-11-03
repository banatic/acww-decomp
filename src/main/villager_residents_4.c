/* villager_residents_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207caa0 @ 0x0207caa0, 0x32 bytes, Thumb
 * func_0207ca74 @ 0x0207ca74, 0x2c bytes, Thumb
 * func_0207ca48 @ 0x0207ca48, 0x2c bytes, Thumb
 * func_0207ca08 @ 0x0207ca08, 0x40 bytes, Thumb
 * func_0207c9b8 @ 0x0207c9b8, 0x50 bytes, Thumb
 */

typedef struct {
    unsigned char data[2028];
} TypeB;

typedef struct {
    unsigned char data[20];
} TypeA;

extern int func_0200363c(int);
extern void *func_02082500(unsigned char);
extern int func_0208150c(void *b);
extern int func_02003704(int t);
extern int func_02003648(int t);
extern void MI_CpuFill8(void *dst, int val, int len);

int func_0207caa0(int a, unsigned int *b)
{
    if (func_0200363c(a) != 0) {
        if ((b[a >> 5] >> (a & 31)) & 1) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}

void func_0207ca74(unsigned int *bitset, int bit_index)
{
    int index;
    unsigned int word;

    if (func_0200363c(bit_index)) {
        index = bit_index >> 5;
        word = bitset[index];
        word |= (1u << (bit_index & 31));
        bitset[index] = word;
    }
}

void func_0207ca48(int a, int *arr, int bit)
{
    if (func_0200363c(bit)) {
        arr[bit >> 5] &= ~(1 << (bit & 31));
    }
}

int func_0207ca08(void *param)
{
    int i;
    void *res;
    for (i = 0; i < 150; i++) {
        res = func_02082500((unsigned char) i);
        if (res != 0) {
            if (*(unsigned char *) ((char *) res + 0x4b) < 2) {
                if (func_0207caa0((unsigned char) ((unsigned char) i), (unsigned int *) param) == 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void func_0207c9b8(TypeA *a, TypeB *b)
{
    int i, t;

    if (func_0207ca08(a)) {
        MI_CpuFill8(a, 0, 20);
        for (i = 0; i < 8; i++) {
            t = func_0208150c(b);
            if (func_02003704(t)) {
                func_0207ca74((unsigned int *) a, func_02003648(t));
            }
            b++;
        }
    }
}
