/* path_walker_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02012c30 @ 0x02012c30, 0x38 bytes, Thumb
 * func_02012c20 @ 0x02012c20, 0x10 bytes, Thumb
 * func_02012bcc @ 0x02012bcc, 0x54 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x88];
    int unk_88;
    int unk_8C;
} UnkStruct_02012bcc;

extern int func_02012c68(void *a, void *b, void *map);
extern int func_02013518(void *a, void *b);
extern void *data_021c80bc;
extern int func_02013738(int, int, int);
extern void func_02013440(UnkStruct_02012bcc *);
extern void func_02012e58(UnkStruct_02012bcc *, void *);

int func_02012c30(void *a, void *b)
{
    if (data_021c80bc != 0) {
        func_02012c68(a, b, data_021c80bc);
        if (func_02013518(a, b) != 0) {
            ((int *) a)[1] = 2;
            return 1;
        }
    }
    return 0;
}

int func_02012c20(int argument0, int argument1, int argument2)
{
    func_02013738((int) argument0, (int) argument1, (int) argument2);
    return 0;
}

int func_02012bcc(UnkStruct_02012bcc *a, void *b)
{
    if (data_021c80bc == 0) {
        goto zero;
    }
    func_02012c20((int) a, (int) b, (int) data_021c80bc);
    if (func_02013518((void *) a, b) != 0) {
        goto one;
    }
    func_02013440(a);
    a->unk_88 = 0;
    a->unk_8C = 2;
    func_02012e58(a, b);
    goto zero;
one:
    return 1;
zero:
    return 0;
}
