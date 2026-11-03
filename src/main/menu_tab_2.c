/* menu_tab_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208bfc8 @ 0x0208bfc8, 0x8 bytes, Thumb
 * func_0208bfc0 @ 0x0208bfc0, 0x8 bytes, Thumb
 * func_0208bfa0 @ 0x0208bfa0, 0x20 bytes, Thumb
 * func_0208bf48 @ 0x0208bf48, 0x56 bytes, Thumb
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad_24[0x4];
    char unk_28;
} UnkStruct_0208bfa0;

struct UnkStruct_0208bf48 {
    unsigned char pad_00[0x26];
    unsigned char unk_26;
};

extern int func_0208c620(char *);
extern int func_0203ec98(void);
extern unsigned int func_020960d8(int x);

void func_0208bfc8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (38))) + (0)) = 1;
}

void func_0208bfc0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (38))) + (0)) = 0;
}

int func_0208bfa0(UnkStruct_0208bfa0 *p)
{
    if (p->unk_20 != 0) {
        goto L0;
    }
    if (func_0208c620(&p->unk_28) == 0) {
        goto L0;
    }
    return 1;
L0:
    return 0;
}

int func_0208bf48(struct UnkStruct_0208bf48 *arg)
{
    int r4 = func_0203ec98() != 0;
    unsigned int a = func_020960d8(4);
    int r1 = (a - 8) <= 7;
    int r2 = (a - 0x24) <= 8;
    if (arg->unk_26 != 0 && !r4 && !r1 && !r2) {
        return 1;
    }
    return 0;
}
