/* func_02072600 @ 0x02072600, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02072600 {
    int count;
    int data[16];
};
void func_02072600(struct UnkStruct_02072600 *p)
{
    unsigned int i;
    p->count = 0;
    i = 0;
    do {
        p->data[i] = 0;
        i++;
    } while (i < 16);
}
