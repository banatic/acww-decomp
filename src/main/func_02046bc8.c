/* func_02046bc8 @ 0x02046bc8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void func_0209e100(void *, int);
extern int func_0209dc48(void *);
extern void func_0204ca8c(int);

void func_02046bc8()
{
    struct {
        int a;
        int b;
        int c;
    } s;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    func_0209e100(&s, 6);
    func_0204ca8c((unsigned char) func_0209dc48(&s));
}
