/* func_ov127_02299d64 @ 0x02299d64, 0x5c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov127_0229989c(void *argument0);
extern int func_ov127_022996d8(int);
extern int func_ov127_02299890(int);
extern int func_ov127_022996c8(int);
extern int func_020896b8(int, const char *, int, const char *, int, int, int);
extern const char data_ov127_0229b5e4[];

int func_ov127_02299d64(int p0, int p1)
{
    int a = func_ov127_0229989c((void *) p0);
    int v = func_ov127_022996d8(p1);
    int t = -a;
    int x = t + 4 + (v << 3);
    int c = func_ov127_02299890(p0);
    int w = func_ov127_022996c8(p1);
    int s = -c;
    int y = s + 4 + (w << 3);

    return func_020896b8(1, data_ov127_0229b5e4, x & 0x1ff, (const char *) y, -1, 2, 0);
}
