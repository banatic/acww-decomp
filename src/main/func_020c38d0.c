/* func_020c38d0 @ 0x020c38d0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void);
extern void func_0201c280(char *, char *);
extern void func_020c3350(char *, char *);
extern int func_020b65c4(void);
extern void func_0201af28(char *, int, int, int, int);
extern void *data_021fbca0;

int func_020c38d0(char *param)
{
    if (func_0202edc8() == 0) {
        return 0;
    }
    data_021fbca0 = param;
    func_0201c280(param, param + 0x658);
    func_020c3350(param + 0x658, param);
    if (func_020b65c4()) {
        func_0201af28(param + 0x350, 2, 0x333, 0xcc, 0x133);
        func_0201af28(param + 0x350, 1, 0x280, 0xcc, 0x133);
    }
    param[0x563] = 1;
    return 1;
}
