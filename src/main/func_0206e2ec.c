/* func_0206e2ec @ 0x0206e2ec, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206dd08(void *dst, int val, int arg);

void func_0206e2ec(char *s, int p2)
{
    int i;

    func_0206dd08(s, 0x75, p2);
    func_0206dd08(s + 0x74, 0x180, p2);

    for (i = 0; i < 4; i++) {
        func_0206dd08(s + 0xe8 + i * 0x74, (unsigned short) (i * 0x28 + 0x9d), p2);
    }

    *(int *) (s + 0x320) = 0;
}
