/* func_02063e1c @ 0x02063e1c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *p);

typedef struct {
    int a;
    int b;
    int c;
} Local_02063e1c;

int func_02063e1c(void)
{
    Local_02063e1c local;

    local.a = 0;
    local.b = 0;
    func_0209e474(&local);
    return ((unsigned char *) &local)[3];
}
