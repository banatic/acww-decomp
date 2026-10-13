/* func_ov109_0229d478 @ 0x0229d478, 0x3c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov109_0229ccc0(void *arg);
extern void func_ov094_0229a084(void *ptr);
extern void func_ov094_0229af20(void *ptr);
extern void func_ov094_0229bbc0(void *ptr);
extern void func_ov002_0220af74(void *ptr);

void func_ov109_0229d478(void *arg)
{
    char *p;

    func_ov109_0229ccc0(arg);
    func_ov094_0229a084((char *) arg + 0x0b54);
    p = (char *) arg;
    p += 0xcc;
    func_ov094_0229af20(p);
    func_ov094_0229bbc0((char *) arg + 0x0b2c);
    func_ov002_0220af74((char *) arg + 0x27e8);
}
