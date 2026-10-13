/* func_020bcda0 @ 0x020bcda0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int data_021f6cd8;
extern int data_020d2354[];
extern void *func_020bdc50(void *work, int a, int b, int c, int d);
extern void func_02065268(int a);

void func_020bcda0(void *work, int p1, int p2, int p3)
{
    int lookup;
    int sub;
    int bitflag;
    int packed;

    if (data_021f6cd8 != 0) {
        bitflag = p2 << 0x1f;
        lookup = data_020d2354[p1];
        lookup = lookup - 0x1d;
        lookup = lookup & 0xf;
        sub = p1 & 3;
        sub = sub << 8;
        packed = p3 << 0x1c;
        lookup = lookup | bitflag;
        sub = sub | lookup;
        packed = packed | sub;
        func_020bdc50(work, 9, 0x3c, 0, packed);
    } else {
        if (p2 != 0) {
            func_02065268(p1 + 5);
        } else {
            func_02065268(p1 + 1);
        }
    }
}
