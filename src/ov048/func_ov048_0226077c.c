/* func_ov048_0226077c @ 0x0226077c, 0x228 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_0226077c;
typedef struct {
    char x[0x40];
} UnkStruct_0226077c_2;

extern int func_020e8b0c(int, int, int);
extern void func_020b5630(UnkStruct_0226077c_2 *);
extern void func_020b45d0(UnkStruct_0226077c_2 *, int, int, int, int, int);
extern void func_02068404(int, int, UnkStruct_0226077c_2 *);
extern void func_020b5618(UnkStruct_0226077c_2 *);

int func_ov048_0226077c(UnkStruct_0226077c *p, int id)
{
    UnkStruct_0226077c_2 a;
    UnkStruct_0226077c_2 b;
    int code;
    int q;

    code = 0x84;
    if (id == 0x4e85 || id == 0x5bcf || func_020e8b0c(id, 0x59d8, 0x5dbf) != 0) {
        code = 0x83;
    } else if (func_020e8b0c(id, 0x4e86, 0x4e8b) != 0 || id == 0x4e8d || func_020e8b0c(id, 0x4e8f, 0x5207) != 0 ||
               func_020e8b0c(id, 0xcb24, 0xcb82) != 0 || func_020e8b0c(id, 0xcc4c, 0xccaf) != 0 ||
               func_020e8b0c(id, 0xcf08, 0xcf6b) != 0 || func_020e8b0c(id, 0xcf6c, 0xcfcf) != 0 ||
               func_020e8b0c(id, 0xcfd0, 0xd033) != 0) {
        code = 0x84;
    } else if (id == 0x4e8c) {
        code = 0x85;
    } else if (id == 0x4e8e) {
        code = 0x86;
    } else if (id == 0xc3b3) {
        code = 0x87;
    } else if (func_020e8b0c(id, 0xc79b, 0xc79e) != 0 || func_020e8b0c(id, 0xc7a0, 0xc7fe) != 0 ||
               func_020e8b0c(id, 0xc864, 0xc8c6) != 0) {
        code = 0x88;
    } else if (id == 0xc79f) {
        code = 0x89;
    } else if (func_020e8b0c(id, 0xc800, 0xc863) != 0) {
        code = 0x8a;
    } else if (func_020e8b0c(id, 0xcb20, 0xcb23) != 0 || func_020e8b0c(id, 0xcb84, 0xcb87) != 0 ||
               func_020e8b0c(id, 0xcbe8, 0xcbeb) != 0) {
        code = 0x8b;
    }

    q = id / 1000;
    func_020b5630(&a);
    func_020b5630(&b);
    func_020b45d0(&a, q, 2, 6, 0, 0);
    func_020b45d0(&b, id - q * 1000, 3, 6, 0, 0);
    func_02068404(p->unk_40, 6, &a);
    func_02068404(p->unk_40, 7, &b);
    func_020b5618(&b);
    func_020b5618(&a);
    return code;
}
