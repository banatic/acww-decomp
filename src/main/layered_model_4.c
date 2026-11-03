/* layered_model_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02054c2c @ 0x02054c2c, 0x80 bytes, Thumb
 * func_02054bac @ 0x02054bac, 0x80 bytes, Thumb
 * func_02054b64 @ 0x02054b64, 0x48 bytes, Thumb
 * func_02054b18 @ 0x02054b18, 0x4c bytes, Thumb
 * func_02054ad0 @ 0x02054ad0, 0x48 bytes, Thumb
 */

typedef struct {
    void *unk_00;       // 0x00
    char pad_04[152];   // 0x04
    void *unk_9C;       // 0x9c
    char pad_A0[24];    // 0xa0
    void *unk_B8;       // 0xb8
    char pad_BC[56];    // 0xbc
    int unk_F4;         // 0xf4
    void *unk_F8;       // 0xf8
    char pad_FC[4];     // 0xfc
    int unk_100;        // 0x100
    int unk_104;        // 0x104
    int unk_108;        // 0x108
    char pad_10C[4];    // 0x10c
    char unk_110[0x3c]; // 0x110
    int unk_14C;        // 0x14c
    int unk_150;        // 0x150
} UnkStruct_02054c2c;

typedef struct UnkStruct_02054bac {
    int *unk_00;
    char pad_04[0x98];
    int *unk_9C;
    char pad_A0[0x18];
    int *unk_B8;
    char pad_BC[0x38];
    int unk_F4;
    int *unk_F8;
    char pad_FC[0x4];
    int unk_100;
    int unk_104;
    int unk_108;
    char pad_10C[0x4];
    char sub110;
    char pad_111[0x3b];
    int unk_14C;
    int unk_150;
} UnkStruct_02054bac;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x98];
    void *unk_9C;
    unsigned char pad_A0[0x18];
    void *unk_B8;
    unsigned char pad_BC[0x3c];
    unsigned char unk_F8[0x18];
    unsigned char unk_110[0x1];
} UnkStruct_02054b64;

typedef struct {
    unsigned int unk_00;
    char pad_04[0x98];
    unsigned int unk_9C;
    char pad_A0[0x18];
    unsigned int unk_B8;
    char pad_BC[0x3c];
    unsigned int unk_F8;
    char pad_FC[0x14];
    unsigned int unk_110;
} UnkStruct_02054ad0;

extern char data_020dd184;
extern void *func_02054e8c(void *);
extern void *func_02056ee0(void *);
extern void func_02056ed4(void *p);
extern void func_02057078(void *p);
extern void *func_02054d9c(void *p);
extern void func_020edb3c(void *);
extern unsigned char data_020dd0ac[];
extern unsigned char data_020dd0bc[];
extern unsigned char data_020dd0cc[];

UnkStruct_02054c2c *func_02054c2c(UnkStruct_02054c2c *obj)
{
    func_02054e8c(obj);
    obj->unk_00 = (void *) ((char *) data_020dd0ac);
    obj->unk_9C = (void *) ((char *) data_020dd0bc);
    obj->unk_B8 = (void *) ((char *) data_020dd0cc);
    obj->unk_F8 = (void *) &data_020dd184;
    obj->unk_100 = 0;
    obj->unk_104 = 0;
    obj->unk_108 = 0x1000;
    func_02056ee0(obj->unk_110);
    obj->unk_F4 = 0;
    obj->unk_14C = 0;
    obj->unk_150 = 0;
    return obj;
}

UnkStruct_02054bac *func_02054bac(UnkStruct_02054bac *self)
{
    func_02054e8c(self);
    self->unk_00 = ((int *) data_020dd0ac);
    self->unk_9C = ((int *) data_020dd0bc);
    self->unk_B8 = ((int *) data_020dd0cc);
    self->unk_F8 = ((int *) &data_020dd184);
    self->unk_100 = 0;
    self->unk_104 = 0;
    self->unk_108 = 0x1000;
    func_02056ee0(&self->sub110);
    self->unk_F4 = 0;
    self->unk_14C = 0;
    self->unk_150 = 0;
    return self;
}

UnkStruct_02054b64 *func_02054b64(UnkStruct_02054b64 *p)
{
    p->unk_00 = (void *) ((unsigned char *) data_020dd0ac);
    p->unk_9C = (void *) ((unsigned char *) data_020dd0bc);
    p->unk_B8 = (void *) ((unsigned char *) data_020dd0cc);
    func_02056ed4(p->unk_110);
    func_02057078(p->unk_F8);
    func_02054d9c(p);
    return p;
}

void *func_02054b18(void *arg)
{
    *((int *) arg) = (int) ((int *) data_020dd0ac);
    *((int *) ((char *) arg + 0x9c)) = (int) ((int *) data_020dd0bc);
    *((int *) ((char *) arg + 0xb8)) = (int) ((int *) data_020dd0cc);
    func_02056ed4((char *) arg + 0x110);
    func_02057078((char *) arg + 0xf8);
    func_02054d9c(arg);
    func_020edb3c(arg);
    return arg;
}

UnkStruct_02054ad0 *func_02054ad0(UnkStruct_02054ad0 *self)
{
    self->unk_00 = (unsigned int) data_020dd0ac;
    self->unk_9C = (unsigned int) data_020dd0bc;
    self->unk_B8 = (unsigned int) data_020dd0cc;
    func_02056ed4(&self->unk_110);
    func_02057078(&self->unk_F8);
    func_02054d9c(self);
    return self;
}
