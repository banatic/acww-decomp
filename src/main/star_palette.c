/* star_palette: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b18ac @ 0x020b18ac, 0x10 bytes, Thumb
 * func_020b18a8 @ 0x020b18a8, 0x2 bytes, Thumb
 * func_020b1800 @ 0x020b1800, 0xa8 bytes, Thumb
 * func_020b177c @ 0x020b177c, 0x84 bytes, Thumb
 * func_020b1774 @ 0x020b1774, 0x8 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    char block0[128];
    char blocks[5][128];
    char arr1[4];
    char arr2[4];
    char unk_32C;
} UnkStruct_020b177c;

extern void *func_020b9cfc(void *);
extern int func_020644cc(int a);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern int func_020b9b14(unsigned char *a, unsigned char *b, unsigned int c, int d, int e);
extern void func_020b9ccc(void *);
extern int func_02064af4(int, void *, int);
extern int func_02002bd0(void *, int, int, int, int);
extern int data_020e4220[5];

void *func_020b18ac(void *arg)
{
    func_020b9cfc(arg);
    return arg;
}

void func_020b18a8(void *object) {}

void func_020b1800(unsigned char *self)
{
    unsigned int flag;
    unsigned int zero_val;
    int i;
    unsigned char *p;

    func_020b9ccc((void *) self);
    flag = 0;
    zero_val = 0;

    for (i = 0; i < 4; i++) {
        p = self + i;
        if (p[0x324] != 0) {
            p[0x324]--;
        } else {
            if (p[0x328] == 0) {
                p[0x328] = (unsigned char) (func_020644cc(4) + 1);
                p[0x324] = (unsigned char) (func_020644cc(15) + 5);
            } else {
                p[0x328] = (unsigned char) zero_val;
                p[0x324] = (unsigned char) (func_020644cc(30) + 10);
            }
            flag = 1;
            MI_CpuCopy8(self + 0xa4 + (p[0x328] << 7) + (i << 5), self + 0x24 + (i << 5), 32);
        }
    }

    if (flag != 0) {
        func_020b9b14(self, self + 0x24, self[0x32c], 4, 7);
    }
}

void func_020b177c(UnkStruct_020b177c *obj, int param1)
{
    int i;

    func_020b9ccc(obj);

    for (i = 0; i < 5; i++) {
        obj->arr1[i] = (char) (func_020644cc(0x5a) + 10);
        obj->arr2[i] = 0;
    }

    obj->unk_32C = (char) param1;

    for (i = 0; i < 5; i++) {
        func_02064af4(data_020e4220[i], &obj->blocks[i], 128);
    }

    MI_CpuCopy8(obj->blocks, &obj->block0, 128);
    func_02002bd0(&obj->block0, param1, 4, 4, 7);
}

void func_020b1774(void *argument0)
{
    func_020b9ccc((void *) argument0);
}
