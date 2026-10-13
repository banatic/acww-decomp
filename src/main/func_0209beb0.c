/* func_0209beb0 @ 0x0209beb0, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c4a8(char *);
extern int func_0209c38c(int);
extern void func_0209c448(char *, int, unsigned char);

void func_0209beb0(char *a, char *b, short *arr)
{
    int id;
    id = func_0209c4a8(b + 0x11);
    if (func_0209c38c(id)) {
        func_0209c448(a + 0x11, id, (unsigned char) (arr[id] * 10 >> 12));
    }
}
