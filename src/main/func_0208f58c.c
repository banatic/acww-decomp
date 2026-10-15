/* func_0208f58c @ 0x0208f58c, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208f58c UnkStruct_0208f58c;
struct UnkStruct_0208f58c {
    void *unk_00;
    int pad_04;
    int pad_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    char sub1[20];
    char sub2[20];
    int unk_44;
    int unk_48;
    char sub3[36];
    unsigned short unk_70;
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
    unsigned char unk_75;
};

extern void func_0208af30(struct UnkStruct_0208f58c *obj);
extern void func_0208a1f8(void *p);
extern void *func_0208f640(void *p);
extern void func_0208f0c4(void *, int);

extern unsigned char data_020e23a0[];

struct UnkStruct_0208f58c *func_0208f58c(struct UnkStruct_0208f58c *obj, char a, int b)
{
    func_0208af30(obj);
    obj->unk_00 = (void *) data_020e23a0;
    obj->unk_0C = 0;
    obj->unk_10 = 0;
    obj->unk_14 = -1;
    obj->unk_18 = b;
    func_0208a1f8((void *) &obj->sub1);
    func_0208a1f8((void *) &obj->sub2);
    obj->unk_44 = 0;
    obj->unk_48 = 0;
    func_0208f640((void *) &obj->sub3);
    obj->unk_70 = 0x50c0;
    obj->unk_72 = a;
    obj->unk_73 = 0;
    obj->unk_74 = 0;
    obj->unk_75 = 0;
    func_0208f0c4(obj, 0);
    return obj;
}
