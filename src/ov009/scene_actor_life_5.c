/* scene_actor_life_5: 6 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_0226552c @ 0x0226552c, 0x6c bytes, Thumb
 * func_ov009_022654c0 @ 0x022654c0, 0x6c bytes, Thumb
 * func_ov009_02265460 @ 0x02265460, 0x60 bytes, Thumb
 * func_ov009_022653fc @ 0x022653fc, 0x64 bytes, Thumb
 * func_ov009_0226539c @ 0x0226539c, 0x60 bytes, Thumb
 * func_ov009_02265398 @ 0x02265398, 0x4 bytes, Thumb
 */

struct UnkStruct_022653fc {
    unsigned int unk_00;
    unsigned char pad_04[0xE8];
    unsigned int unk_EC;
    unsigned char pad_F0[0x4C];
    unsigned int unk_13C;
    unsigned char pad_140[0xB4];
    unsigned int unk_1F4;
    unsigned char pad_1F8[0x40];
    unsigned int unk_238;
    unsigned char pad_23C[0x56];
    unsigned char unk_292[4];
};

extern void *func_0203f130(void *p);
extern void *func_02066a30(void *p);
extern void *func_02055210(void *p);
extern void *func_020b33e0(void *p);
extern void *func_ov009_02262f8c(void *p);
extern void func_0209d34c(void *p);
extern void func_0209d340(void *);
extern void *func_ov009_02262f74(void *);
extern void *func_020b33b8(void *);
extern void *func_020551e0(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern void func_020edf54(void *);
extern unsigned char data_ov009_022658dc[];
extern unsigned char data_ov009_022659a0[];

void *func_ov009_0226552c(void *obj)
{
    func_0203f130(obj);
    func_02066a30((char *) obj + 0xec);
    *(void **) obj = (void *) ((char *) data_ov009_022658dc);
    *(void **) ((char *) obj + 0xec) = (void *) ((char *) data_ov009_022659a0);
    *(unsigned short *) ((char *) obj + 0x136) = 0xfff1;
    func_02055210((char *) obj + 0x13c);
    func_020b33e0((char *) obj + 0x1f4);
    func_ov009_02262f8c((char *) obj + 0x238);
    func_0209d34c((char *) obj + 0x292);
    return obj;
}

void *func_ov009_022654c0(void *p)
{
    func_0203f130(p);
    func_02066a30((void *) ((unsigned int) p + 0xEC));
    *(void **) ((unsigned int) p) = ((char *) data_ov009_022658dc);
    *(void **) ((unsigned int) p + 0xEC) = ((char *) data_ov009_022659a0);
    *(unsigned short *) ((unsigned int) p + 0x136) = 0xFFF1;
    func_02055210((void *) ((unsigned int) p + 0x13C));
    func_020b33e0((void *) ((unsigned int) p + 0x1F4));
    func_ov009_02262f8c((void *) ((unsigned int) p + 0x238));
    func_0209d34c((void *) ((unsigned int) p + 0x292));
    return p;
}

void *func_ov009_02265460(void *self)
{
    *(void **) self = ((int *) data_ov009_022658dc);
    *(void **) ((char *) self + 0xec) = ((int *) data_ov009_022659a0);
    func_0209d340((char *) self + 0x292);
    func_ov009_02262f74((char *) self + 0x238);
    func_020b33b8((char *) self + 0x1f4);
    func_020551e0((char *) self + 0x13c);
    func_02066994((char *) self + 0xec);
    func_0203f080(self);
    return self;
}

struct UnkStruct_022653fc *func_ov009_022653fc(struct UnkStruct_022653fc *p)
{
    p->unk_00 = (unsigned int) (unsigned int) data_ov009_022658dc;
    p->unk_EC = (unsigned int) (unsigned int) data_ov009_022659a0;
    func_0209d340((void *) &p->unk_292);
    func_ov009_02262f74((void *) &p->unk_238);
    func_020b33b8((void *) &p->unk_1F4);
    func_020551e0((void *) &p->unk_13C);
    func_02066994((void *) &p->unk_EC);
    func_0203f080((void *) p);
    func_020edf54((void *) p);
    return p;
}

void *func_ov009_0226539c(void *self)
{
    *(void **) self = ((int *) data_ov009_022658dc);
    *(void **) ((char *) self + 0xec) = ((int *) data_ov009_022659a0);
    func_0209d340((char *) self + 0x292);
    func_ov009_02262f74((char *) self + 0x238);
    func_020b33b8((char *) self + 0x1f4);
    func_020551e0((char *) self + 0x13c);
    func_02066994((char *) self + 0xec);
    func_0203f080(self);
    return self;
}

int func_ov009_02265398(void *object)
{
    return 1;
}
