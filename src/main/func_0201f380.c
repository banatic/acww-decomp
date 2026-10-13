/* func_0201f380 @ 0x0201f380, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203fdc4(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int data_020c8ba0;

struct UnkStruct_0201f380 {
    void *unk_00;
    unsigned char unk_04;
};

void func_0201f380(char *a, struct UnkStruct_0201f380 *b)
{
    int x;
    int r4, r6;

    x = func_0203fdc4(0x10);
    if (x < 0) {
        x = 0;
    }

    if (x == 0) {
        r4 = 2;
        r6 = 0;
    } else if (x >= 1 && x <= 5) {
        r4 = 3;
        r6 = 2;
    } else {
        r4 = 2;
        r6 = 5;
    }

    func_0202da38(a, a + 0x104, a + 0x122, 0x1e, func_020036e8(func_0208150c(*(int *) (*(int *) (a + 0x100) + 0x830))),
                  data_020c8ba0, 1, r6, (unsigned char) r4);

    b->unk_00 = a + 0x104;
    b->unk_04 = *(unsigned char *) (a + 0x122);
}
