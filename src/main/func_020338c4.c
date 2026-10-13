/* func_020338c4 @ 0x020338c4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203428c(void *p, int a, int b);
extern void func_0202f6ac(void *p, int a, int b, int c);

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} UnkStruct_020338c4;

int func_020338c4(UnkStruct_020338c4 *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    func_0203428c((void *) ((char *) a1 + 0x20), a7, a8);
    func_0202f6ac(a1, a2, a3, a4);
    a1->unk_28 = a6;
    a1->unk_2C = a5;
    return 1;
}
