/* func_0207b764 @ 0x0207b764, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0207b764 {
    char data[0x2c];
};

extern struct UnkStruct_0207b764 *func_02079350(void);
extern int func_020794d0(struct UnkStruct_0207b764 *);
extern void func_0209bd5c(void *);

void func_0207b764(void)
{
    struct UnkStruct_0207b764 *p;
    int i;

    p = func_02079350();
    for (i = 0; i < 8; i++) {
        func_0209bd5c((void *) func_020794d0(p));
        p++;
    }
}
