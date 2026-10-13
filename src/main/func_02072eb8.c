/* func_02072eb8 @ 0x02072eb8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02062e50(void *);
extern void func_02072ea4(void *, void *);
extern void func_020a8a70(void *, void *, int, int);
extern void func_02062e00(void *);

void func_02072eb8(void *param0, void *param1)
{
    void *sp[9]; // 0x24 bytes

    func_02062e50(sp);
    func_02072ea4(param0, sp);
    func_020a8a70(param1, sp, 0, 0);
    func_02062e00(sp);
}
