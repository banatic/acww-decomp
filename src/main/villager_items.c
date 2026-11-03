/* villager_items: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207de70 @ 0x0207de70, 0x44 bytes, Thumb
 * func_0207de14 @ 0x0207de14, 0x5c bytes, Thumb
 * func_0207ddd0 @ 0x0207ddd0, 0x44 bytes, Thumb
 */

typedef struct {
    char pad_00[0x7b0];
    unsigned short arr[1];
} UnkStruct_0207de70;

extern int func_0207deb4(UnkStruct_0207de70 *p, unsigned short *);
extern void func_0207df88(UnkStruct_0207de70 *p);
extern void func_020782d8(UnkStruct_0207de70 *p, int a);
extern unsigned short *func_0207dfd4(int, int);
extern int func_020644cc(int);
extern int func_0204c878(unsigned short *);

int func_0207de70(UnkStruct_0207de70 *p, unsigned short *argument1)
{
    int idx;
    idx = func_0207deb4(p, (unsigned short *) argument1);
    if (idx == -1) {
        goto error;
    }
    p->arr[idx] = 0xfff1;
    func_0207df88(p);
    func_020782d8(p, (int) func_0207dfd4((int) p, 0));
    return 1;
error:
    return 0;
}

void func_0207de14(unsigned short *out, int in)
{
    unsigned short *arr;
    int count, i, k;

    *out = 0xfff1;
    arr = func_0207dfd4(in, 0);
    count = 0;
    for (i = 0; i < 4; i++) {
        if (arr[i] != 0xfff1) {
            count++;
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        i = 0;
        while (i < 4) {
            if (*arr != 0xfff1) {
                if (k == 0) {
                    *out = *arr;
                    break;
                }
                k--;
            }
            arr++;
            i++;
        }
    }
}

void func_0207ddd0(unsigned short *out, int arg2)
{
    unsigned short *p;
    int best;
    int score;
    int i;

    *out = 0xfff1;
    p = func_0207dfd4(arg2, 0);
    best = 0;
    for (i = 0; i < 4; p++, i++) {
        if (*p == 0xfff1) {
            continue;
        }
        score = func_0204c878(p);
        if (score < best) {
            continue;
        }
        *out = *p;
        best = score;
    }
}
