/* func_020a0c18 @ 0x020a0c18, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a0c18 {
    char pad_00[0x24];
};

extern void *func_02099664(int a);
extern void *func_02077bc8(void *p);
extern void *func_02077d68(void *);
extern void *func_02099658(int a);
extern void func_02077d00(void);
extern void *func_02077c3c(struct UnkStruct_020a0c18 *p);
extern int func_020eb058(void *a, void *b);

int func_020a0c18(int a, int b, int c)
{
    void *x;
    struct UnkStruct_020a0c18 *arr;
    void *y;
    int i;

    x = (func_02077d68((void *) func_02077bc8(func_02099664(b))));
    asm {
        add r0, c, #0
        bl func_02099658
        bl func_02077d00
        add arr, r0, #0
    }
    for (i = 0; i < 0x20; i++)
    {
        y = (func_02077d68((void *) func_02077c3c(&arr[i])));
        if (y != 0 && func_020eb058(x, y) != 0) {
            return 1;
        }
    }
    return 0;
}
