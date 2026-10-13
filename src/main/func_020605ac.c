/* func_020605ac @ 0x020605ac, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060904(int);
extern int func_020606fc(int, int);
extern int func_020608fc(void);
extern int func_02064af4(int, int, int);

int func_020605ac(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r0 = c;
    int r6 = func_02060904(r0);
    int r4_2 = func_020606fc(r5, r4);
    int r2 = func_020608fc();
    return func_02064af4(r6, r4_2, r2);
}
