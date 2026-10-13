/* func_0209e140 @ 0x0209e140, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209de24(int a, int b);
extern void func_0209e1ac(void *p, int a);

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} Struct0209e140;

void func_0209e140(Struct0209e140 *p, int n)
{
    int r4;
    int x;

    r4 = p->unk_03;
    if (p->unk_04 == 1) {
        x = func_0209de24(p->unk_05, 12);
    } else {
        x = func_0209de24(p->unk_05, (unsigned char) (p->unk_04 - 1));
    }

    r4 = r4 - n;

    while (r4 <= 0) {
        if (r4 == 0) {
            r4 = x;
        } else {
            r4 = r4 + x;
        }

        func_0209e1ac(p, 1);

        if (p->unk_04 == 1) {
            x = func_0209de24(p->unk_05, 12);
        } else {
            x = func_0209de24(p->unk_05, (unsigned char) (p->unk_04 - 1));
        }
    }

    p->unk_03 = (unsigned char) r4;
}
