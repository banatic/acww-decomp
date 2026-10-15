/* func_0204f260 @ 0x0204f260, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f828(unsigned int *p0, unsigned int *p1, unsigned int p2);
extern int func_0204f2b8(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);

int func_0204f260(unsigned int a, unsigned int b)
{
    unsigned int arr[4];

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
    func_0204f828(&arr[0], &arr[2], b);
    return func_0204f2b8(a, arr[0], arr[1], arr[2], arr[3]);
}
