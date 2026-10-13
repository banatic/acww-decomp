/* func_020af974 @ 0x020af974, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020af974 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};
extern void *func_020afad4(void *p);
extern void func_0209e140(void *p, int n);

int func_020af974(int a, unsigned char *b)
{
    unsigned char local[8];
    if (((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_03 == 0) {
        goto ret0_late;
    }
    *(unsigned int *) &local[0] = 0;
    *(unsigned int *) &local[4] = 0;
    local[5] = ((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_02;
    local[4] = ((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_01;
    local[3] = ((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_00;
    local[2] = 6;
    local[1] = 0;
    local[0] = 0;
    *(unsigned short *) &local[6] = 0;
    func_0209e140(local, 1);
    if (local[5] == b[5] && local[4] == b[4] && local[3] == b[3]) {
        return 1;
    }
    return 0;
ret0_late:
    return 0;
}
