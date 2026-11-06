/* town_beach: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02046f7c @ 0x02046f7c, 0x28 bytes, Thumb
 * func_02046f14 @ 0x02046f14, 0x68 bytes, Thumb
 * func_02046ebc @ 0x02046ebc, 0x58 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int count;
} Param1;

typedef struct {
    unsigned char data[0x90];
} UnkStruct_02046f14;

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_02046fa4(int);
extern void func_02047050(int);
extern UnkStruct_02046f14 data_021c7a08[];
extern void func_0209def4(void *ptr);
extern void *func_02047114(void *ptr);
extern int func_02048cb8(void *a, void *b, int c, int d, void *e, int (*predicate)(int, int, int), int g);
extern int func_02048e34(int, int, int);
extern unsigned char data_021c779c[];
extern int func_020644cc(int);
extern int func_0204e414(void);

void func_02046f7c(int arg)
{
    if (func_02073d90(data_020ccf94) != 0) {
        func_02046fa4(arg);
    } else {
        func_02047050(arg);
    }
}

void func_02046f14(void *param0, Param1 *param1)
{
    int i, j;
    unsigned char used;
    int local0 = 0;
    int limit;

    limit = param1->count - 2;

    for (i = 0; i < limit; i++) {
        used = *((unsigned char *) &data_021c7a08[i] + 0x88);
        j = 2 - used;
        while (j > 0) {
            func_02048cb8(param0, param1, i + 1, 4, func_02047114(param0), (((int (*)(int, int, int)) func_02048e34)), local0);
            j--;
        }
    }
    func_0209def4((void *) data_021c779c);
}

int func_02046ebc(int param)
{
    int r5 = func_020644cc(4);
    int local = func_0204e414();
    int r4 = 0;
    int r6 = r4;
    while (r4 < 4) {
        if (func_02048cb8((void *) param, (void *) local, r5 + 1, 4, (void *) 0x1520,
                          (((int (*)(int, int, int)) func_02048e34)), r6) != 0) {
            return 1;
        }
        r5 = (r5 + 1) & 3;
        r4++;
    }
    return 0;
}
