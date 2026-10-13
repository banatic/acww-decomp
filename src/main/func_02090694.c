/* func_02090694 @ 0x02090694, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064b2c(int, void *, int, int);
extern void *data_021d52c8;

struct Entry {
    int unk_00[3];
};
extern struct Entry data_020e26ec[];

void func_02090694(int *out, int *src)
{
    int index = *(volatile int *) src;
    int i = 0;
    int a = 0;
    int b = 0;

    for (; i < 3; i++) {
        struct Entry *e = &data_020e26ec[index];
        if (e->unk_00[i] != 0) {
            out[i] = func_02064b2c(e->unk_00[i], data_021d52c8, 4, a);
        } else {
            out[i] = b;
        }
    }
}
