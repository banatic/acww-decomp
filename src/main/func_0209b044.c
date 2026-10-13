/* func_0209b044 @ 0x0209b044, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    unsigned char unk_0C;
    unsigned char unk_0D;
} UnkStruct_0209b044;

extern unsigned int func_0209b184(UnkStruct_0209b044 *);
extern void func_0209b160(UnkStruct_0209b044 *, unsigned int);
extern void func_0209bb90(UnkStruct_0209b044 *, int);
extern int func_020644cc(int);
extern void func_0209bb68(UnkStruct_0209b044 *, unsigned short *);
extern unsigned int func_0209b1f0(UnkStruct_0209b044 *, int);
extern const unsigned short data_020d1a28[2];

int func_0209b044(UnkStruct_0209b044 *obj)
{
    unsigned int r;
    unsigned short v;

    if (obj->unk_0D != 0) {
        r = func_0209b184(obj);
        if (r < 5) {
            func_0209b160(obj, r);
            obj->unk_0C = r;
            func_0209bb90(obj, 0);
            v = data_020d1a28[func_020644cc(10) & 1];
            func_0209bb68(obj, &v);
            r = func_0209b1f0(obj, obj->unk_0D);
            if ((r == 2 && (func_020644cc(10) & 1) != 0) || r == 1) {
                obj->unk_0D = 0;
            }
            return 1;
        }
        obj->unk_0D = 0;
    }
    return 0;
}
