/* func_020bc68c @ 0x020bc68c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *, int, int, int);
extern void func_020bc9c4(void *, int);
extern void func_020bcd30(void *);

void func_020bc68c(void *obj)
{
    int value;

    value = *((int *) ((char *) obj + 0x2f30));
    if (value < 0) {
        func_020bca80(obj, 0, 0xc8, 0);
    } else if (value == 0) {
        func_020bc9c4(obj, 4);
    }
    func_020bcd30(obj);
}
