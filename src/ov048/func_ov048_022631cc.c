/* func_ov048_022631cc @ 0x022631cc, 0x6c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x564];
    int unk_564;
    char pad_568[0xe6e - 0x568];
    unsigned short unk_E6E;
} UnkStruct_022631cc;

extern int func_0209615c(int);
extern int func_02095a8c(int, int);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_020644cc(int);
extern unsigned short data_020c80f8;

int func_ov048_022631cc(UnkStruct_022631cc *obj)
{
    if (func_0209615c(4) == 0) {
        func_02095a8c(-0x8000, 4);
        func_02019d0c(&obj->unk_564, 3, 1, 0, 0, 0, -0x4000, 0, 0, data_020c80f8, 0);
        obj->unk_E6E = (unsigned char) (func_020644cc(5) + 5);
        return 1;
    }
    return 0;
}
