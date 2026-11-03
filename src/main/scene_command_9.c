/* scene_command_9: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02015848 @ 0x02015848, 0x2 bytes, Thumb
 * func_02015828 @ 0x02015828, 0x1e bytes, Thumb
 * func_02015800 @ 0x02015800, 0x28 bytes, Thumb
 * func_020157d4 @ 0x020157d4, 0x2c bytes, Thumb
 */

typedef struct UnkStruct_02015828 {
    char pad_00[0x68];
    int unk_68;
} UnkStruct_02015828;

typedef struct {
    char pad_00[0x78];
    int (*unk_78)(unsigned short *, int);
    unsigned short unk_7C;
    unsigned short unk_7E;
    char pad_80[4];
    unsigned char unk_84;
    char pad_85[3];
    unsigned char unk_88;
} UnkStruct_020157d4;

int func_0201596c(UnkStruct_02015828 *p, int arg);

void func_02015848(void *object, int state)
{
    (void) object;
    (void) state;
}

int func_02015828(UnkStruct_02015828 *p, int x)
{
    int result = 0;
    if (func_0201596c(p, result)) {
        p->unk_68 = x;
        result = 1;
    }
    return result;
}

void func_02015800(void *arg0, unsigned short arg1, unsigned char arg2, unsigned char arg3)
{
    unsigned short *ptr1;
    int (**ptr2)(unsigned short *, int);
    unsigned char *ptr3;
    unsigned char *ptr4;
    unsigned short *ptr5;
    unsigned char *ptr6;

    ptr1 = (unsigned short *) ((char *) arg0 + 0x7c);
    *ptr1 = arg1;
    ptr2 = (int (**)(unsigned short *, int))((char *) arg0 + 0x78);
    *ptr2 = 0;
    ptr3 = (unsigned char *) ((char *) arg0 + 0x84);
    *ptr3 = arg2;
    ptr5 = (unsigned short *) ((char *) arg0 + 0x7e);
    *ptr5 = 0xfff1;
    ptr6 = (unsigned char *) ((char *) arg0 + 0x88);
    *ptr6 = arg3;
}

void func_020157d4(UnkStruct_020157d4 *s, int (*val1)(unsigned short *, int), unsigned char val2, unsigned char val3)
{
    s->unk_7C = 0;
    s->unk_78 = val1;
    s->unk_84 = val2;
    s->unk_7E = 0xfff1;
    s->unk_88 = val3;
}
