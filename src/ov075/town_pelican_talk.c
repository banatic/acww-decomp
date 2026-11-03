/* town_pelican_talk: 3 functions, module ov075
 * mwccarm 1.2/base -O4,s
 * func_ov075_02278b24 @ 0x02278b24, 0x40 bytes, Thumb
 * func_ov075_02278b00 @ 0x02278b00, 0x24 bytes, Thumb
 * func_ov075_02278aec @ 0x02278aec, 0x12 bytes, Thumb
 */

typedef struct {
    char pad_00[0xb8];
    void *ptr;
} UnkStruct_02278b24;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_02278b24_2;

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_020644cc(int);
extern char data_ov075_02279aa8[];
extern int func_02015590(void *p, int a);
extern void func_ov075_02278d44(void *p, int a);
extern int func_020160b4(void *parameter0);
extern unsigned int func_020ab504(void *);

void func_ov075_02278b24(UnkStruct_02278b24 *self, UnkStruct_02278b24_2 *obj)
{
    unsigned char flag;

    obj->unk_04 = 0x1a;
    flag = ((unsigned char *) self->ptr)[0x718];
    if (flag != 0) {
        if (func_02099020(func_020984e8(), 6)) {
            obj->unk_04 = func_020644cc(4) + 0xc;
        }
    }
    obj->unk_00 = data_ov075_02279aa8;
}

void func_ov075_02278b00(void *p)
{
    func_020984e8();
    if (*(unsigned char *) ((char *) p + 0x1e) == 0x1a) {
        func_02015590(p, 0);
        func_ov075_02278d44(p, 1);
    }
}

void func_ov075_02278aec(void *arg0)
{
    func_020ab504((void *) func_020160b4((void *) arg0));
}
