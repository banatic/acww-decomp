/* func_0209dbe4 @ 0x0209dbe4, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[3];
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
} UnkStruct_0209dbe4;

extern void func_0209dc10(unsigned char *arr);

void func_0209dbe4(UnkStruct_0209dbe4 *p)
{
    unsigned char arr[4];
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 0;
    arr[3] = 0;
    arr[2] = p->b2;
    arr[1] = p->b1;
    arr[0] = p->b0;
    func_0209dc10(arr);
}
