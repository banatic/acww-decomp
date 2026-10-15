/* func_020bb568 @ 0x020bb568, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct S_020bb568 {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x1524 - 0x1210];
    int unk_1524;
    int unk_1528;
    int unk_152C;
    int unk_1530;
    char pad_1534[0x1578 - 0x1534];
    int unk_1578;
    char pad_157C[0x1584 - 0x157c];
    int unk_1584;
    int unk_1588;
    int unk_158C;
} S_020bb568;

extern int func_020bb66c(S_020bb568 *p, int a, int b);
extern int func_020bb608(S_020bb568 *p, int *a, int *b, int c, int d);
extern void func_020bb7e0(S_020bb568 *p, int a, int b);
extern void func_020bbc90(S_020bb568 *p);

void func_020bb568(S_020bb568 *p)
{
    int mode;
    int idx;

    if (p->unk_1530 == 0) {
        mode = 1;
        idx = p->unk_1524 + 1;
    } else {
        mode = 2;
        idx = p->unk_1524 - 1;
    }

    if (func_020bb66c(p, idx, 6) != 0) {
        if (func_020bb608(p, &p->unk_1584, &p->unk_1588, mode, idx) != 0) {
            func_020bb7e0(p, p->unk_1524, idx);
            if (p->unk_1524 < 3 && p->unk_1528 >= 3) {
                func_020bbc90(p);
            }
            p->unk_1578 = 0;
            p->unk_120C = 0;
            p->unk_158C = 2;
        }
    }
}
