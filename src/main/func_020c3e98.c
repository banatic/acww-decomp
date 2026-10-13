/* func_020c3e98 @ 0x020c3e98, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c400(void *a, void *b);
extern void func_0201c280(void *a, void *b);
extern void func_020c3c20(void *obj, int val);

int func_020c3e98(void *self)
{
    unsigned short local = 0xfff1;

    if (func_0202edc8(self) == 0) {
        return 0;
    }
    local = 0xd000;
    func_0201c400(self, &local);
    func_0201c280(self, (char *) self + 0x658);
    func_020c3c20((char *) self + 0x658, (int) self);
    return 1;
}
