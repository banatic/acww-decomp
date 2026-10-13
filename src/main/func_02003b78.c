/* func_02003b78 @ 0x02003b78, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02003b78_2 {
    int data[5];
};
struct UnkStruct_02003b78 {
    int unk_00;
    char pad_04[8];
    struct UnkStruct_02003b78_2 sub;
    int arr0;
    int arr1;
    int arr2;
    int arr3;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    int c;
    int d;
    int e;
};

extern void func_0208af30(struct UnkStruct_02003b78 *p);
extern void func_0208a1f8(struct UnkStruct_02003b78_2 *s);

extern unsigned char data_020d72cc[];

struct UnkStruct_02003b78 *func_02003b78(struct UnkStruct_02003b78 *p)
{
    func_0208af30(p);
    p->unk_00 = (unsigned int) data_020d72cc;
    func_0208a1f8(&p->sub);
    p->arr0 = 0;
    p->arr1 = 0;
    p->arr2 = 0;
    p->arr3 = 0;
    p->b0 = 0;
    p->b1 = 0;
    p->b2 = 1;
    p->b3 = 0;
    p->c = 0;
    p->d = 5;
    p->e = 0;
    return p;
}
