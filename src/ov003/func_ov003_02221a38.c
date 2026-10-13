/* func_ov003_02221a38 @ 0x02221a38, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    int unk_04;
    unsigned short unk_08;
    char pad_0A[0x60 - 0xa];
    char sub[0x44];
} Elem;

extern void func_0200451c(void *ptr);

void func_ov003_02221a38(Elem *arr)
{
    int i = 0;
    int value = i;
    unsigned short mask = 0xfff1;

    for (; i < 0x14; i++) {
        char *sub;
        arr->unk_04 = value;
        arr->unk_08 = mask;
        sub = (char *) arr;
        sub += 0x60;
        func_0200451c(sub);
        arr++;
    }
}
