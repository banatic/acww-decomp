/* func_ov113_0229a404 @ 0x0229a404, 0x70 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void *);
extern void func_02070b84(void *);

void func_ov113_0229a404(void *p)
{
    char *base = (char *) p;
    int i;

    func_020b9ccc(base + 0x26a0);
    func_020b9ccc(base + 0x26c4);
    func_02070b84(base + 0x26e8);
    func_02070b84(base + 0x2754);
    func_02070b84(base + 0x27c0);
    func_02070b84(base + 0x282c);

    for (i = 0; i < 6; i++) {
        func_02070b84(base + 0x2898 + i * 0x6c);
    }
}
