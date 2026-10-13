/* func_020bc758 @ 0x020bc758, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *, int, int, int);
extern void func_020bc9c4(void *, int);
extern void func_020bcab0(void *);

void func_020bc758(void *p)
{
    int field;

    field = *(int *) ((char *) p + 0x2f30);
    if (field < 0) {
        func_020bca80(p, 80, 150, 500);
    } else if (field == 0) {
        func_020bc9c4(p, 20);
    }
    func_020bcab0(p);
}
