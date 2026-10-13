/* func_0200c610 @ 0x0200c610, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010680(void *p, unsigned short *val);
extern int func_0201063c(void *p);

typedef struct {
    unsigned short unk_00;
    unsigned char pad[10];
    unsigned char unk_0C;
} UnkStruct_0200c610;

typedef struct {
    char pad[0x7d4];
    UnkStruct_0200c610 sub;
} UnkStruct_0200c610_2;

void func_0200c610(UnkStruct_0200c610_2 *p)
{
    UnkStruct_0200c610 *q;
    unsigned short val;

    q = &p->sub;
    if (q->unk_0C == 0) {
        val = q->unk_00;
        func_02010680(p, &val);
        if (func_0201063c(p) != 0) {
            q->unk_0C = 1;
        }
    }
}
