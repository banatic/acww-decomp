/* func_ov090_0229934c @ 0x0229934c, 0x1e bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022080a0(void *obj, int a, int b);
extern void func_02001c08(int a);

void func_ov090_0229934c(void *obj)
{
    char *p;
    p = (char *) obj;
    p += 0x8c;
    *p = 2;
    func_ov002_022080a0(obj, 1, 2);
    func_02001c08(1);
}
