/* func_020ac9a4 @ 0x020ac9a4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e3fb4;

typedef struct {
    void *data;
    int unk_04;
    short arr[5];
    char unk_12;
    int unk_14;
    short unk_18;
    short unk_1A;
    short unk_1C;
    short unk_1E;
} Func_020ac9a4_struct;

void func_020ac9a4(Func_020ac9a4_struct *p)
{
    unsigned int i;

    p->data = &data_020e3fb4;
    p->unk_04 = 0;
    p->unk_12 = 0;
    p->unk_14 = 0;
    p->unk_18 = 0;
    p->unk_1A = 0;
    p->unk_1C = 0;
    p->unk_1E = 0;

    i = 0;
    do {
        p->arr[i] = 0;
        i++;
    } while (i < 5);
}
