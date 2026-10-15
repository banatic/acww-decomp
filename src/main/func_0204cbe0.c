/* func_0204cbe0 @ 0x0204cbe0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_0204cbe0;

extern UnkStruct_0204cbe0 *func_0204cc04(int);

void func_0204cbe0(void *object)
{
    UnkStruct_0204cbe0 *p;
    int i;

    p = func_0204cc04(0);
    for (i = 0; i < 4; i++) {
        p->unk_00 = 99;
        p->unk_04 = 1;
        p->unk_08 = 1;
        p++;
    }
}
