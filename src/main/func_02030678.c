/* func_02030678 @ 0x02030678, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203071c(void *obj, const void *, unsigned int);

typedef struct {
    char unk_00[0x10];
    int unk_10;
} UnkStruct_02030678;

void *func_02030678(UnkStruct_02030678 *obj, int a, int b, int c)
{
    func_0203071c(obj, (const void *) a, (unsigned int) b);
    obj->unk_10 = c;
    return obj;
}
