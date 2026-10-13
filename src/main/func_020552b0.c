/* func_020552b0 @ 0x020552b0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02055454(void *);

struct UnkStruct_020552b0_2 {
    char data[0x9c];
};

struct UnkStruct_020552b0 {
    int unk_00;
    unsigned int count;
    struct UnkStruct_020552b0_2 *array;
};

int func_020552b0(struct UnkStruct_020552b0 *p)
{
    int i;
    int result = 1;
    if (p->count == 0) {
        return 1;
    }
    for (i = 0; i < p->count; i++) {
        result &= func_02055454(&p->array[i]);
    }
    p->count = 0;
    return 1;
}
