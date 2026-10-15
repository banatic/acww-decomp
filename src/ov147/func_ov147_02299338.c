/* func_ov147_02299338 @ 0x02299338, 0x3c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int data_021ee418;
extern void *func_020900f0(void *buffer);
int func_02065ec0(int);
int func_020900f4(int *);
void func_0206844c(int, char *, int);

void func_ov147_02299338(void *self)
{
    int *p = &data_021ee418;
    if (func_02065ec0((int) func_020900f0(p)) == 0) {
        return;
    }
    if (func_020900f4(p) != 0) {
        return;
    }
    {
        char c = 0x35;
        func_0206844c(*(int *) ((char *) self + 0x40), &c, 0);
    }
}
