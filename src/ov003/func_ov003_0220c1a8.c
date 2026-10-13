/* func_ov003_0220c1a8 @ 0x0220c1a8, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220bfe8(void *);
extern int func_020b6590(void);
extern void func_020b7d84(int, void *, void *, int, int, int);

int func_ov003_0220c1a8(void *s)
{
    int v;

    func_ov003_0220bfe8(s);
    v = func_020b6590();
    func_020b7d84(v, (char *) s + 0x138, (char *) s + 0x5c, 0xc00, 9, (unsigned char) (((unsigned int *) s)[2]));
    return 1;
}
