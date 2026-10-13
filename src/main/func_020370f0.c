/* func_020370f0 @ 0x020370f0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da324;

typedef struct {
    int *ptr;
    int val;
    unsigned short flags;
    unsigned char a;
    unsigned char b;
} func_020370f0_struct;

void func_020370f0(func_020370f0_struct *obj, int value)
{
    obj->ptr = &data_020da324;
    obj->val = value;
    obj->flags = 0xffff;
    obj->a = 0;
    obj->b = 0;
}
