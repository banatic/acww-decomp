/* func_0209b56c @ 0x0209b56c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[12];
    char arr[2][16];
    char flag;
} UnkStruct0209b56c;

extern void func_0209bd5c(UnkStruct0209b56c *arg);
extern void func_02003738(char *p);

void func_0209b56c(UnkStruct0209b56c *arg)
{
    int i;
    func_0209bd5c(arg);
    for (i = 0; i < 2; i++) {
        func_02003738(arg->arr[i]);
    }
    arg->flag = 0;
}
