/* layer_load_task_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9c7c @ 0x020b9c7c, 0x4e bytes, Thumb
 * func_020b9c68 @ 0x020b9c68, 0x12 bytes, Thumb
 */

extern unsigned int func_020ba0dc(char *);
extern void func_020ba0a8(char *);
extern void func_020ba07c(char *);
extern void func_020ba040(char *);
extern void func_020b9ccc(void *);

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

void func_020b9c68(void *arg)
{
    void *r4 = arg;
    func_020b9ccc(arg);
    ((unsigned char *) r4)[0xd] = 1;
}
