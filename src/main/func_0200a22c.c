/* func_0200a22c @ 0x0200a22c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7d4];
    char sub;
} UnkStruct_0200a22c;

extern void func_020109fc(void *p, int a, int b, int c);
extern int func_0200a24c(void *ptr);

int func_0200a22c(UnkStruct_0200a22c *p)
{
    func_020109fc(p, 1, 3, 0);
    return func_0200a24c(&p->sub);
}
