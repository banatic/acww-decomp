/* func_ov121_0229af7c @ 0x0229af7c, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *, void *, int, int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern void func_ov121_0229a358(int);

void func_ov121_0229af7c(int p0, char p1, int p2)
{
    char c;
    c = data_021f43ec;
    c = p1;
    func_ov002_0220b9b8((void *) (p0 + 0x40c), &c, p2, 0);
    func_ov002_02208098(p0, 19);
    func_ov121_0229a358(p0);
}
