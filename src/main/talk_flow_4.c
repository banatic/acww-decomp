/* talk_flow_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067c04 @ 0x02067c04, 0x1c bytes, Thumb
 * func_02067be0 @ 0x02067be0, 0x24 bytes, Thumb
 * func_02067bb8 @ 0x02067bb8, 0x28 bytes, Thumb
 * func_02067b54 @ 0x02067b54, 0x64 bytes, Thumb
 * func_02067b3c @ 0x02067b3c, 0x18 bytes, Thumb
 * func_02067b1c @ 0x02067b1c, 0x20 bytes, Thumb
 */

typedef struct {
    char pad_00[0x13b8];
    char unk_13B8;
} UnkStruct_02067c04;

extern void func_0206bd24(void *ptr);
extern void func_020676c8(void *ptr);
extern void func_0206841c(void *);
extern void func_0206bd44(void *);
extern void func_0206c0f0(void *);
extern void func_0206bd14(void *);
extern void func_02067948(void *);
extern void func_020678d4(void *);
extern void func_02067ab0(void *);
extern void func_02067a64(void *);
extern void func_02067a2c(void *);
extern void func_020679ec(void *);
extern void func_020679a0(void *);
extern void func_0206785c(void *);
extern void func_0206780c(void *);
extern void func_020677c0(void *);
extern void func_0206776c(void *);
extern void func_02067718(void *);
extern void func_02067af8(void *);
extern void func_02067ac0(void *);
extern void func_02068434(void *);

void func_02067c04(UnkStruct_02067c04 *arg)
{
    func_0206bd24(&arg->unk_13B8);
    func_020676c8(arg);
}

void func_02067be0(void *param)
{
    void *obj;
    void *vtable;
    void (*func)(void *);

    func_0206841c(param);
    func_02067c04((UnkStruct_02067c04 *) param);
    obj = *(void **) ((char *) param + 0x14a8);
    vtable = *(void **) obj;
    func = *(void (**)(void *))((char *) vtable + 0x74);
    func(obj);
}

void func_02067bb8(void *param)
{
    func_0206bd44((char *) param + 0x13b8);
    func_0206c0f0((char *) param + 0x684);
    func_02067be0(param);
}

void func_02067b54(void *p)
{
    func_0206bd14((char *) p + 0x13b8);
    func_02067948(p);
    func_020678d4(p);
    func_02067ab0(p);
    func_02067a64(p);
    func_02067a2c(p);
    func_020679ec(p);
    func_020679a0(p);
    func_0206785c(p);
    func_0206780c(p);
    func_020677c0(p);
    func_0206776c(p);
    func_02067718(p);
    func_02067bb8(p);
}

void func_02067b3c(unsigned char *r4)
{
    unsigned char r1 = 0;
    func_02067b54(r4);
    r4[0x1e99] = r1;
}

void func_02067b1c(void *p)
{
    func_02067b3c((unsigned char *) p);
    func_02067af8(p);
    func_02067ac0(p);
    func_02068434(p);
}
