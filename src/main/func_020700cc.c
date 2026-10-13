/* func_020700cc @ 0x020700cc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *data_020df5ec[];
extern void func_0204f8ec(int);
extern void func_0206ff74(int);
extern void func_0206ff00(int);

int func_020700cc(int x)
{
    int *p = data_020df5ec[x];
    int i;

    for (i = 0; p[i] != -1; i++) {
        func_0204f8ec(p[i]);
    }
    func_0206ff74(x);
    func_0206ff00(x);
    return 1;
}
