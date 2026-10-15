/* func_ov002_022082d8 @ 0x022082d8, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov002_0220bb24;
extern char data_020da13c;
extern void *func_ov002_022087bc(void *);
extern void func_ov002_022089d4(void *);
extern void func_020ee62c(void *);

typedef struct {
    char data[0x10];
} Sub50;
typedef struct {
    char data[0x10];
} Sub70;

typedef struct {
    void *vtbl;
    char pad_04[0x50 - 4];
    Sub50 unk_50;
    char pad2[0x70 - 0x50 - sizeof(Sub50)];
    Sub70 unk_70;
} UnkStruct_022082d8;

UnkStruct_022082d8 *func_ov002_022082d8(UnkStruct_022082d8 *p)
{
    p->vtbl = &data_ov002_0220bb24;
    func_ov002_022087bc(&p->unk_70);
    func_ov002_022089d4(&p->unk_50);
    p->vtbl = &data_020da13c;
    func_020ee62c(p);
    return p;
}
