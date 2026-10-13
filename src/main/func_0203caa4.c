/* func_0203caa4 @ 0x0203caa4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203caa4 {
    short a;
    short b;
    int c;
    int d;
    int e;
    int unk_10;
};

extern struct UnkStruct_0203caa4 data_020ca20c[];

void func_0203caa4(void *param0, int index, struct UnkStruct_0203caa4 *dst)
{
    if (dst == 0) {
        dst = (struct UnkStruct_0203caa4 *) ((char *) param0 + 0xfc);
    }
    dst->d = data_020ca20c[index].d;
    dst->e = data_020ca20c[index].e;
    dst->unk_10 = data_020ca20c[index].unk_10;
    dst->c = data_020ca20c[index].c;
    dst->b = data_020ca20c[index].b;
    dst->a = data_020ca20c[index].a;
}
