/* scene_action_6: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201489c @ 0x0201489c, 0x2 bytes, Thumb
 * func_02014898 @ 0x02014898, 0x2 bytes, Thumb
 * func_0201487c @ 0x0201487c, 0x1c bytes, Thumb
 * func_02014868 @ 0x02014868, 0x14 bytes, Thumb
 * func_0201481c @ 0x0201481c, 0x4c bytes, Thumb
 */

typedef struct {
    int unk_00;
    short unk_04;
    short unk_06;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned char unk_0E;
} UnkStruct_0201487c;

typedef struct UnknownStructA {
    char pad_00[0x40];
    unsigned int unk_40;
} UnknownStructA;

typedef struct ParentStruct {
    char pad_00[0x634];
    UnknownStructA *unk_634;
} ParentStruct;

extern void *func_02015d68(void *p);
extern int func_02068370(unsigned int arg);
extern void func_0201a7d4(void *p);
extern void func_0201a7cc(void *p);

void func_0201489c(void *object) {}

void func_02014898(void *object) {}

void func_0201487c(UnkStruct_0201487c *arg0)
{
    arg0->unk_08 = 5;
    arg0->unk_09 = 5;
    arg0->unk_0A = 0;
    arg0->unk_04 = 0;
    arg0->unk_06 = 0;
    arg0->unk_0B = 0;
    arg0->unk_00 = 5;
    arg0->unk_0D = 1;
    arg0->unk_0C = 0;
    arg0->unk_0E = 0;
}

int func_02014868(const unsigned char *p)
{
    if (p[9] < 5 || p[8] < 5) {
        return 1;
    }
    return 0;
}

void func_0201481c(void *unused, ParentStruct *param)
{
    UnknownStructA *p;
    void *ptr;
    p = param->unk_634;
    if (p == 0) {
        return;
    }
    if (p->unk_40 == 0) {
        return;
    }
    ptr = func_02015d68(p);
    if (ptr == 0) {
        return;
    }
    if (func_02068370(p->unk_40) != 0) {
        func_0201a7d4((char *) ptr + 0x418);
    } else {
        func_0201a7cc((char *) ptr + 0x418);
    }
}
