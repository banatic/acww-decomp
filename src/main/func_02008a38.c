/* func_02008a38 @ 0x02008a38, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02008a38 UnkStruct_02008a38;
extern void func_020109fc(UnkStruct_02008a38 *p, int a, int b, int c);
void func_02008a38(UnkStruct_02008a38 *p, int q, int c)
{
    int t = 0;
    if (c) {
        t = 5;
    }
    func_020109fc(p, 0x81, t, t);
}
