/* func_020bf568 @ 0x020bf568, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf3c8(void *, int);

extern int data_021f6cdc;

void func_020bf568(unsigned char *p0, unsigned char p1, int p2)
{
    int v;

    p0[0x2e] = p1;
    if (p0[0x2e] != 0) {
        v = 0;
    } else {
        v = data_021f6cdc;
    }
    *(int *) (p0 + 0x28) = v;
    func_020bf3c8(p0, p2);
}
