/* func_02092e14 @ 0x02092e14, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094c38(void *param0, int param1, void *param2);
extern char data_020d1750;

typedef struct {
    char pad_00[0xc];
    void *ptr;
} UnkStruct_02092e14;

void func_02092e14(UnkStruct_02092e14 *a)
{
    func_02094c38(a, 0, &data_020d1750);
    *((char *) a->ptr + 0x69) = 0;
    *((int *) ((char *) a->ptr + 0x4c)) = 0x3d;
    *((int *) ((char *) a->ptr + 0x50)) = 0x466;
}
