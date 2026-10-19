/* func_020f5360 @ 0x020f5360, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd234;
extern void func_020efc50(void *);
extern void func_020eed48(void *);

struct UnkStruct_020f5360 {
    char pad_00[8];
    char resource;
    char pad_09[15];
    unsigned short w;
    unsigned char b1;
    unsigned char b2;
};

void func_020f5360(struct UnkStruct_020f5360 *p, int value)
{
    data_021fd234 = value;
    p->w = 0;
    p->b2 = 0;
    p->b1 = p->b2;
    func_020efc50(p);
    func_020eed48(&p->resource);
}
