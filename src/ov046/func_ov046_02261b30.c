/* func_ov046_02261b30 @ 0x02261b30, 0x3c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov046_02261270(void *a, void *b);

int func_ov046_02261b30(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov046_02261270((char *) p + 0x658, p);
    *(int *) ((char *) p + 0x740) = -1;
    return 1;
}
