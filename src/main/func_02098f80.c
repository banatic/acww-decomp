/* func_02098f80 @ 0x02098f80, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066650(char *);
extern void func_02065cc8(char *);
extern void func_02098aa0(char *, int, int);

void func_02098f80(char *arg)
{
    int i, j;
    for (i = 0; i < 10; i++) {
        func_02066650(arg + (i << 8));
    }
    func_02065cc8(arg + 0xA00);
    for (j = 0; j < 15; j++) {
        *(unsigned short *) (arg + j * 2 + 0xA4A) = 0xFFF1;
    }
    func_02098aa0(arg, 0, 1);
}
