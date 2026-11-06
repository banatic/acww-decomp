/* path_walker_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02012a4c @ 0x02012a4c, 0x4c bytes, Thumb
 * func_02012a18 @ 0x02012a18, 0x34 bytes, Thumb
 */

typedef struct {
    int unk_00;
    char pad_04[4];
    int unk_08;
} UnkStruct_02012a18;

extern int data_021c80bc;
extern int func_0204f704(int, int);
extern int func_02037e8c(int);
extern void func_020131dc(int *arg0, int arg1, int arg2, int arg3);
extern void *func_0204f61c(void *s, unsigned int x, unsigned int y, unsigned int z);

void func_02012a4c(int *out, int param2)
{
    int tested_value0;
    int r4 = data_021c80bc;
    int local[2];
    int result;

    out[0] = 0;
    out[1] = 0;

    if (r4 != 0) {
        if ((tested_value0 = (int) (func_0204f704(r4, 0x200))) != 0) {
            result = func_02037e8c(tested_value0);
            func_020131dc(local, param2, result, r4);
            out[0] = local[0];
            out[1] = local[1];
        }
    }
}

int func_02012a18(void *unused, UnkStruct_02012a18 *p)
{
    void *g = (*(void **) &data_021c80bc);
    int result = 0;
    unsigned int x, y;
    if (g == 0) {
        goto done;
    }
    x = (unsigned int) (p->unk_00 >> 17);
    y = (unsigned int) (p->unk_08 >> 17);
    if (func_0204f61c(g, x, y, 0x200) == 0) {
        goto done;
    }
    result = 1;
done:
    return result;
}
