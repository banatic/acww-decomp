/* func_0200ad8c @ 0x0200ad8c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_0200b374(void *p);
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_02010d64(void *p);
extern int func_02010ca4(void *p);
extern void func_0200b218(void *p);
extern void func_0200ae7c(void *p, unsigned char *ptr, unsigned char byte);
extern int func_0200f530(void *p, unsigned int *arr);
extern void func_0200ae04(void *p);

typedef struct {
    unsigned char pad_00[0x7d4];
    unsigned char sub[0x2c];
    unsigned int flags;
} UnkStruct_0200ad8c;

void func_0200ad8c(UnkStruct_0200ad8c *p)
{
    func_0200b374(p);
    if (func_02073908(data_020ccf94, p->flags)) {
        func_02010d64(p);
        func_02010ca4(p);
        func_0200b218(p);
        {
            unsigned char *sub = p->sub;
            func_0200ae7c(p, sub + 8, *sub);
        }
    } else {
        unsigned char *sub = (unsigned char *) p + 0x7d4;
        unsigned int arr[2];
        unsigned int v1 = sub[0xa];
        unsigned int v0 = sub[9];
        arr[0] = v0;
        arr[1] = v1;
        func_0200f530(p, arr);
        func_02010d64(p);
        func_0200b218(p);
        func_0200ae04(p);
    }
}
