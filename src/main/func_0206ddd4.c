/* func_0206ddd4 @ 0x0206ddd4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206dbd8(int, int);

void func_0206ddd4(int r0)
{
    int r4;
    int r5;
    int r6;
    int r7;

    r5 = r0;
    func_0206dbd8(r5, 0);
    func_0206dbd8(r5 + 0x74, 1);
    r4 = 0;
    r5 += 0xe8;
    r6 = r4;
    r7 = 0x74;
    do {
        func_0206dbd8(r5 + r4 * r7, r6);
        r4++;
    } while (r4 < 4);
}
