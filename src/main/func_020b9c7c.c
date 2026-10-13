/* func_020b9c7c @ 0x020b9c7c, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba0dc(char *);
extern void func_020ba0a8(char *);
extern void func_020ba07c(char *);
extern void func_020ba040(char *);

int func_020b9c7c(char *obj)
{
    unsigned char b = obj[0xe];
    switch (b - 4) {
        case 0:
            func_020ba0dc(obj + 0x10);
            break;
        case 1:
            func_020ba0a8(obj + 0x10);
            break;
        case 2:
            func_020ba07c(obj + 0x10);
            break;
        case 3:
            func_020ba040(obj + 0x10);
            break;
        default:
            return 0;
    }
    return 1;
}
