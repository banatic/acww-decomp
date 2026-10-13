/* func_ov002_0220830c @ 0x0220830c, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da13c;
extern int data_ov002_0220bb24;
extern void func_020ee660(void *p);
extern void func_ov002_022089e0(void *sub);
extern void func_ov002_022087d4(void *sub);

struct UnkStruct_0220830c {
    int *vptr;
    char pad_04[0x4c];
    char sub1[0x14];
    int unk_64;
    int unk_68;
    char pad_6C[4];
    char sub2[1];
};

struct UnkStruct_0220830c *func_ov002_0220830c(struct UnkStruct_0220830c *obj)
{
    func_020ee660(obj);
    obj->vptr = &data_020da13c;
    obj->vptr = &data_ov002_0220bb24;
    func_ov002_022089e0(obj->sub1);
    obj->unk_64 = 0;
    obj->unk_68 = 0;
    func_ov002_022087d4(obj->sub2);
    return obj;
}
