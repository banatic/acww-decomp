/* func_020becbc @ 0x020becbc, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020becbc {
    int unk_00;
    char arr[4];
};

void func_020becbc(struct UnkStruct_020becbc *p, int n)
{
    if (n < 0) {
        unsigned i = 0;
        goto test;
    loop:
        p->arr[i] = -1;
        i++;
    test:
        if (i < 4) {
            goto loop;
        }
    } else {
        p->arr[n - 12] = -1;
    }
}
