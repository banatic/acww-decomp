/* func_ov047_0226063c @ 0x0226063c, 0x4c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov047_02261ae8(void);
extern void func_020157d4(void *, void (*)(void), int, int);
extern void func_02015828(void *, int);
extern void func_ov047_02261f84(void *, int);
extern int func_0209f150(void *, int);
extern int data_021dc7a8;

void func_ov047_0226063c(void *obj, int flag)
{
    if (flag == 0) {
        func_020157d4(obj, func_ov047_02261ae8, 0xd, 0);
        func_02015828(obj, 0);
        func_ov047_02261f84(obj, 2);
    } else {
        if (func_0209f150(&data_021dc7a8, 0xc) != 0) {
            *((int *) ((char *) obj + 0xd0)) = 0xea;
        } else {
            *((int *) ((char *) obj + 0xd0)) = 0xe9;
        }
    }
}
