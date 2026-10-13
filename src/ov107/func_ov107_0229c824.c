/* func_ov107_0229c824 @ 0x0229c824, 0x70 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229c294(void *, int);
extern int func_ov107_0229d388(void *, unsigned char);
extern void func_ov107_0229c894(void *, int);
extern int func_ov002_022088cc(int);
extern void func_ov002_0220a2b4(void *);

int func_ov107_0229c824(void *obj, int p1)
{
    unsigned char orig = *(unsigned char *) ((char *) obj + 0xb8);
    func_ov107_0229c294(obj, 0x18);
    if (p1 == 0) {
        return 0;
    }
    if (func_ov107_0229d388(obj, *(unsigned char *) ((char *) obj + 0xb8)) != 0) {
        func_ov107_0229c894(obj, p1);
    } else {
        if (*(unsigned char *) ((char *) obj + 0xb8) == 0xf && func_ov002_022088cc(p1) != 0) {
            *(unsigned char *) ((char *) obj + 0xb8) = 0xe;
            func_ov002_0220a2b4((char *) obj + 0x22b4);
        }
    }
    if (orig == *(unsigned char *) ((char *) obj + 0xb8)) {
        return 0;
    } else {
        return 1;
    }
}
