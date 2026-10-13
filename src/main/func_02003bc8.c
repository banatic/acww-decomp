/* func_02003bc8 @ 0x02003bc8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02003bc8 {
    int unk_00;
    int val;
    unsigned int count;
    char pad_0C[9];
    unsigned char flag;
} UnkStruct_02003bc8;

extern signed char data_020c7588[];
extern int func_02003cc0(UnkStruct_02003bc8 *p);
extern int func_02003c98(UnkStruct_02003bc8 *p);
extern void func_02011f2c(unsigned char c);

void func_02003bc8(UnkStruct_02003bc8 *p)
{
    int a, b;

    a = func_02003cc0(p);
    b = func_02003c98(p);

    if (a && b) {
        if (p->count < 4) {
            p->count += 1;
            p->val = data_020c7588[p->count];
        }
    } else {
        if (p->count != 0) {
            p->count -= 1;
            p->val = data_020c7588[p->count];
        }
    }

    if (a && !b && p->count == 0) {
        p->flag = !p->flag;
        func_02011f2c(p->flag);
    }
}
