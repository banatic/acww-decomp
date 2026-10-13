/* func_020ac0ac @ 0x020ac0ac, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac9a4(void *);
extern void func_020aca04(void *);
extern void func_0208f518(void *, int, int);
extern void func_020acb94(void *);
extern unsigned char data_020e3fe4[];

typedef struct {
    void *vtable;
    char pad_04[0x1c];
    char sub1[0x4c];
    char sub2[0x78];
    char sub3[0x58];
    int unk_13C;
    char unk_140[6];
} UnkStruct_020ac0ac;

UnkStruct_020ac0ac *func_020ac0ac(UnkStruct_020ac0ac *obj)
{
    func_020ac9a4(obj);
    obj->vtable = data_020e3fe4;
    func_020aca04(&obj->sub1);
    func_0208f518(&obj->sub2, 1, 0);
    func_020acb94(&obj->sub3);
    obj->unk_13C = 0;
    obj->unk_140[0] = 0;
    obj->unk_140[1] = 0;
    obj->unk_140[2] = 0;
    obj->unk_140[3] = 0;
    obj->unk_140[4] = 0;
    obj->unk_140[5] = 0;
    return obj;
}
