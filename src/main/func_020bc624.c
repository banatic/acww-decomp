/* func_020bc624 @ 0x020bc624, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *p, int a, int b, int c);
extern void func_020bc9c4(void *p, int a);
extern void func_020bcc70(void *p);

void func_020bc624(void *param)
{
    int value = *(int *) ((char *) param + 0x2f30);
    if (value < 0) {
        func_020bca80(param, 0, 100, 0);
    } else if (value == 0) {
        func_020bc9c4(param, 1);
    }
    func_020bcc70(param);
}
