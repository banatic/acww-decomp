/* func_0207df18 @ 0x0207df18, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207df88(void *a, unsigned short *v);
extern int func_0207deb4(void *a, unsigned short *v);
extern int func_0207dfd4(void *a, int x);
extern void func_020782d8(void *a, int x);

typedef struct {
    unsigned char pad_00[0x7b0];
    unsigned short arr[4];
} UnkStruct_0207df18;

void func_0207df18(UnkStruct_0207df18 *a, unsigned short *newVal)
{
    int idx;
    int i;
    unsigned short empty;

    func_0207df88(a, newVal);
    empty = 0xfff1;
    idx = func_0207deb4(a, &empty);
    if (idx != -1) {
        a->arr[idx] = *newVal;
    } else {
        for (i = 0; i < 3; i++) {
            a->arr[i] = a->arr[i + 1];
        }
        a->arr[3] = *newVal;
    }
    func_020782d8(a, func_0207dfd4(a, 0));
}
