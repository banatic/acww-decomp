/* talk_windows_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aa82c @ 0x020aa82c, 0x10 bytes, Thumb
 * func_020aa820 @ 0x020aa820, 0xc bytes, Thumb
 * func_020aa808 @ 0x020aa808, 0x18 bytes, Thumb
 * func_020aa7fc @ 0x020aa7fc, 0xc bytes, Thumb
 * func_020aa7f4 @ 0x020aa7f4, 0x6 bytes, Thumb
 * func_020aa7e8 @ 0x020aa7e8, 0xc bytes, Thumb
 * func_020aa79c @ 0x020aa79c, 0x4c bytes, Thumb
 * func_020aa770 @ 0x020aa770, 0x2c bytes, Thumb
 * func_020aa740 @ 0x020aa740, 0x30 bytes, Thumb
 */

struct _func_020aa82c_s {
    char *ptr;
    unsigned char byte;
};

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
} UnkStruct_020aa7f4;

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
    unsigned char sub_c[0x78];
    unsigned char sub_84[0x30];
    int unk_B4;
    int unk_B8;
    int unk_BC;
    unsigned char unk_C0;
} UnkStruct_020aa79c;

extern void func_020edb3c(void *this);
extern unsigned char data_020e408c[];
extern void func_020ab354(void *arg, void *);
extern int data_020e406c;
extern void *func_020ac2ec(void *obj);
extern void func_020ab37c(void *dst, void *src);
extern int func_020ab36c(void *);
extern void *func_020ac2c8(void *);

void func_020aa82c(struct _func_020aa82c_s *s)
{
    s->ptr = ((char *) data_020e408c);
    s->byte = 0;
}

void func_020aa820(int **p)
{
    *p = ((int *) data_020e408c);
}

void *func_020aa808(void *arg)
{
    *(unsigned int *) arg = (unsigned int) data_020e408c;
    func_020edb3c(arg);
    return arg;
}

void func_020aa7fc(void **pp)
{
    *pp = ((char *) data_020e408c);
}

void func_020aa7f4(UnkStruct_020aa7f4 *p)
{
    p->unk_04 = 1;
}

void func_020aa7e8(void *arg, void *argument1)
{
    func_020ab354((char *) arg + 0x84, (void *) argument1);
}

UnkStruct_020aa79c *func_020aa79c(UnkStruct_020aa79c *obj)
{
    func_020aa82c((struct _func_020aa82c_s *) obj);
    obj->unk_00 = &data_020e406c;
    obj->unk_08 = 0;
    func_020ac2ec(&obj->sub_c);
    func_020ab37c(&obj->sub_84, &obj->sub_c);
    obj->unk_B4 = 0;
    obj->unk_B8 = 0;
    obj->unk_BC = 0;
    obj->unk_C0 = 0;
    return obj;
}

void *func_020aa770(void *this)
{
    *((int **) this) = &data_020e406c;
    func_020ab36c((char *) this + 0x84);
    func_020ac2c8((char *) this + 0xc);
    func_020aa7fc((void **) this);
    return this;
}

void *func_020aa740(void *obj)
{
    *(void **) obj = ((char *) &data_020e406c);
    func_020ab36c((void *) ((char *) obj + 0x84));
    func_020ac2c8((void *) ((char *) obj + 0xc));
    func_020aa7fc((void **) obj);
    func_020edb3c(obj);
    return obj;
}
