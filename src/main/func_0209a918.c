/* func_0209a918 @ 0x0209a918, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x70];
    char data[1];
} UnkStruct_0209a918;

extern int func_0209ad9c(UnkStruct_0209a918 *p, int flag);
extern int func_0209b4d8(int a, int b, int c, char *d);

void func_0209a918(UnkStruct_0209a918 *p)
{
    int ret;
    ret = func_0209ad9c(p, 0);
    func_0209b4d8(ret, 17, 0, p->data);
}
