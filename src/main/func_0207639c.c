/* func_0207639c @ 0x0207639c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a7820(unsigned char *p);
extern void func_020736bc(void *a, unsigned char *b, int c);
extern void func_020a77dc(unsigned char *p1, int *p2, unsigned char *p3, unsigned char *p4, unsigned char *p5, int *p6);
extern void func_020a7394(int a, unsigned char b, unsigned char c, unsigned char d, int e);
extern int func_020a7810(unsigned char *p);
extern void *data_020ccf94;

void func_0207639c(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char arr[8];
    int x;
    int y;

    func_020a7820(arr + 3);
    func_020736bc(data_020ccf94, arr + 3, 2);
    func_020a77dc(arr + 3, &x, arr, arr + 1, arr + 2, &y);
    func_020a7394(x, arr[0], arr[1], arr[2], y);
    func_020a7810(arr + 3);
}
