/* scene_share_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201c0e0 @ 0x0201c0e0, 0x64 bytes, Thumb
 * func_0201c0c8 @ 0x0201c0c8, 0x18 bytes, Thumb
 * func_0201c054 @ 0x0201c054, 0x74 bytes, Thumb
 * func_0201c040 @ 0x0201c040, 0x14 bytes, Thumb
 * func_0201c014 @ 0x0201c014, 0x2c bytes, Thumb
 * func_0201bfd8 @ 0x0201bfd8, 0x3c bytes, Thumb
 * func_0201bfbc @ 0x0201bfbc, 0x1c bytes, Thumb
 */

extern int data_020ccf94;
extern int func_02073d90(int g);
extern unsigned char *func_02085148(void *p);
extern int func_020a7278(void);
extern void func_020850e8(unsigned int, unsigned int, unsigned int, unsigned int);
extern int func_02085174(void *a, int b, int c);
extern int func_02073dd4(int g, int field);
extern unsigned char *func_0201c444(void *self);
extern void func_020771cc(void *a, void *buf, int c, int d);
extern int func_020850b8(int, int, int);
extern void __arm MI_CpuCopy8(char *ptr, int a, unsigned int b);

int func_0201c0e0(void *selfv)
{
    unsigned char *self = (unsigned char *) selfv;
    int g;
    unsigned char *rec;
    int result;

    g = data_020ccf94;
    if (func_02073d90(g) == 0) {
        goto result1;
    }
    if (self[0x563] != 0) {
        goto result1;
    }

    rec = func_02085148(self + 0xea);
    if (rec == 0) {
        goto result0;
    }
    if (rec[0] == 0) {
        goto result0;
    }

    if ((rec[1] == 4 && func_020a7278() != 0) || rec[1] == *(int *) ((unsigned char *) g + 0x64)) {
        result = 1;
    } else {
        result = 0;
    }
    return result;

result0:
    result = 0;
    return result;
result1:
    result = 1;
    return result;
}

void func_0201c0c8(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    func_020850e8(a1, a2, a3, a0 + 0xea);
}

void func_0201c054(void *selfv, int p1, int p2, int p3)
{
    unsigned char *self = (unsigned char *) selfv;
    unsigned char *rec;

    func_02085174(self + 0xea, p2, p3);

    if (func_02073dd4(data_020ccf94, *(int *) ((unsigned char *) data_020ccf94 + 0x64)) != 0) {
        if (func_0201c0e0(self) != 0) {
            int type = (*(unsigned short *) (self + 0xea) & 0xf000) >> 12;
            if (type == 0xe) {
                rec = func_0201c444(self);
                func_020771cc(rec + 0xc, &p1, 0, 0);
            } else if (type == 0xd) {
                rec = func_0201c444(self);
                func_020771cc(rec + 0x20, &p1, 0, 0);
            }
        }
    }
}

int func_0201c040(int p0, int p1, int p2)
{
    return func_020850b8(p1, p2, (p0 + 234));
}

int func_0201c014(int param)
{
    int arr[3];
    arr[0] = 4;
    arr[1] = 4;
    if (func_0201c040(param, (int) (&arr[0]), (int) (&arr[1])) != 0) {
        if (arr[1] < 4) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int func_0201bfd8(char *param0, int param1, unsigned int param2)
{
    void *ptr;
    if (*(unsigned char *) (param0 + 0x563) != 0) {
        goto fail;
    }
    ptr = (void *) func_02085148(param0 + 0xEA);
    if (param2 > 4) {
        param2 = 4;
    }
    if (ptr == 0) {
        goto fail;
    }
    MI_CpuCopy8((char *) ptr + 0x0B, param1, param2);
    return 1;
fail:
    return 0;
}

void func_0201bfbc(int a, int b, int c)
{
    if (c > 4) {
        c = 4;
    }
    MI_CpuCopy8((char *) b, a + 0x62d, c);
}
