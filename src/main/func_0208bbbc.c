/* func_0208bbbc @ 0x0208bbbc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    char pad_04[8];
    char sub_c[20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    int unk_38;
    char sub_3c[64];
    int unk_7C;
    unsigned char unk_80;
    unsigned char unk_81;
    unsigned char unk_82;
} UnkStruct_0208bbbc;

extern void func_0208af30(UnkStruct_0208bbbc *obj);
extern void func_0208a1f8(char *p);
extern void func_020b5630(char *p);

extern unsigned char data_020e21fc[];

UnkStruct_0208bbbc *func_0208bbbc(UnkStruct_0208bbbc *obj)
{
    char *p;
    func_0208af30(obj);
    obj->unk_00 = (void *) data_020e21fc;
    p = (char *) obj;
    p += 0xc;
    func_0208a1f8(p);
    obj->unk_20 = 0;
    obj->unk_24 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_34 = -1;
    obj->unk_38 = 0;
    p = (char *) obj;
    p += 0x3c;
    func_020b5630(p);
    obj->unk_7C = 0;
    p = (char *) obj;
    p += 0x80;
    *p = 0;
    p = (char *) obj;
    p += 0x81;
    *p = 0;
    p = (char *) obj;
    p += 0x82;
    *p = 0;
    return obj;
}
