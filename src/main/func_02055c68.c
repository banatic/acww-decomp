/* func_02055c68 @ 0x02055c68, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02055c54(void *obj, int arg, void *ptr);

struct UnkStruct_02055c68 {
    int unk_00;
    int unk_04;
    void *unk_08;
};

int func_02055c68(void *obj, int arg)
{
    return func_02055c54(obj, arg, ((struct UnkStruct_02055c68 *) obj)->unk_08);
}
