/* func_020c3c08 @ 0x020c3c08, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d315c;

struct UnkStruct_020c3c08 {
    int *ptr;
    char flag;
};

int func_020c3c08(int unused, struct UnkStruct_020c3c08 *s)
{
    s->ptr = &data_020d315c;
    s->flag = 0;
    return 0;
}
