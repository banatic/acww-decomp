/* func_0208ecd0 @ 0x0208ecd0, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c8c9c;
extern int func_0203ec98(void);
extern int func_020b65c4(void);
extern int func_020960d8(int);

int func_0208ecd0(void)
{
    unsigned int a = (data_021c8c9c == 0);
    unsigned int b = (func_0203ec98() == 0);
    unsigned int c = (func_020b65c4() == 6);
    unsigned int x = func_020960d8(4);
    unsigned int d = (x - 8) <= 7;
    unsigned int e = (x - 0x24) <= 8;

    if (a != 0 && b != 0 && c == 0 && d == 0 && e == 0) {
        return 1;
    } else {
        return 0;
    }
}
