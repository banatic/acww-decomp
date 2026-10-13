/* func_ov051_02261364 @ 0x02261364, 0x40 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *obj);
extern void func_0201c280(void *a, void *b);
extern void func_ov051_0226101c(void *a, void *b);
extern void func_0201b38c(void *a, int b);

int func_ov051_02261364(void *obj)
{
    if (func_0202edc8(obj) == 0) {
        return 0;
    }
    func_0201c280(obj, (char *) obj + 0x658);
    func_ov051_0226101c((char *) obj + 0x658, obj);
    func_0201b38c((char *) obj + 0x2a0, 0xfb);
    return 1;
}
