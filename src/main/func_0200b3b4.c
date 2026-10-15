/* func_0200b3b4 @ 0x0200b3b4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200b794(void *, int *, void *, unsigned short *, unsigned char *);
extern int func_0200b7e8(void *p0, int *p1, int p2, int p3, int p4, short p5);

void func_0200b3b4(void *self, short arg2)
{
    char *base = (char *) self;
    unsigned char *byte = (unsigned char *) base;
    struct {
        signed char a;
        unsigned char b;
        unsigned short c;
    } st;
    int arr[2];
    int copy[2];

    if (byte[0x8ec] != 0) {
        byte[0x8ec]++;
        return;
    }
    if (*(int *) (base + 0x7f0) != 0) {
        return;
    }

    arr[0] = 0;
    arr[1] = 0;
    func_0200b794(base + 0x8f0, arr, &st, &st.c, &st.b);
    if (st.a >= 0) {
        return;
    }

    copy[0] = arr[0];
    copy[1] = arr[1];
    func_0200b7e8(base, copy, st.c, st.b, 6, arg2);
}
