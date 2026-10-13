/* func_0201481c @ 0x0201481c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02015d68(void *p);
extern int func_02068370(unsigned int arg);
extern void func_0201a7d4(void *p);
extern void func_0201a7cc(void *p);

typedef struct UnknownStructA {
    char pad_00[0x40];
    unsigned int unk_40;
} UnknownStructA;

typedef struct ParentStruct {
    char pad_00[0x634];
    UnknownStructA *unk_634;
} ParentStruct;

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
