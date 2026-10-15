/* func_ov107_0229cdcc @ 0x0229cdcc, 0x50 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, void *a, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov107_0229cdcc(unsigned char *obj)
{
    void *a = func_ov002_02208ae4(obj + 0x2318);
    int b = func_ov002_02208ad8(obj + 0x2318, obj[0xbd]);
    func_ov002_0220a08c(obj + 0x22b4, a, b, 2);
    obj[0xbb] = obj[0x8d];
    func_ov002_02208098((void *) (obj), 8);
}
