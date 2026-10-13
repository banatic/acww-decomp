/* func_020bc720 @ 0x020bc720, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} Struct020bc720;

extern void func_020bca80(void *arg, int a, int b, int c);
extern void func_020bc9c4(void *arg, int a);
extern int func_020bcab0(void *arg);

int func_020bc720(void *arg)
{
    int val;

    val = ((Struct020bc720 *) arg)->unk_2F30;
    if (val < 0) {
        func_020bca80(arg, 0x8c, 0x96, 0x258);
    } else if (val == 0) {
        func_020bc9c4(arg, 0x14);
    }
    return func_020bcab0(arg);
}
