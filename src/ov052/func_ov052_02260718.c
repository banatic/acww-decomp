/* func_ov052_02260718 @ 0x02260718, 0x13c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02260718 UnkStruct_02260718;
struct Vt {
    void (*unk_00)(UnkStruct_02260718 *);
    void (*unk_04)(UnkStruct_02260718 *);
    void (*unk_08)(UnkStruct_02260718 *);
};
struct UnkStruct_02260718 {
    struct Vt *vt;
};

#define OBJ ((UnkStruct_02260718 *) (a + 0x658))

extern void func_ov052_02261908(void *, int);
extern int func_0201c2a4(void *, int);
extern void func_02016108(UnkStruct_02260718 *, int);
extern int func_ov052_022610c4(UnkStruct_02260718 *);
extern int *func_02095794(int);
extern int func_02030818(int *);
extern void func_020307f8(int);
extern int func_020b5e10(void);
extern void func_020b6098(int, int);

void func_ov052_02260718(char *a, unsigned int cmd, int v)
{
    int t[3];

    a[0x560] = (char) v;
    switch (cmd) {
        case 3:
            func_ov052_02261908(a, 8);
            break;
        case 1:
            OBJ->vt->unk_08(OBJ);
            func_02016108(OBJ, func_0201c2a4(a, 4));
            if (func_ov052_022610c4(OBJ) == 0) {
                func_ov052_02261908(a, 5);
                break;
            }
            if (func_ov052_022610c4(OBJ) == 1 || func_ov052_022610c4(OBJ) == 2 || func_ov052_022610c4(OBJ) == 0xc) {
                func_ov052_02261908(a, 6);
            } else {
                func_ov052_02261908(a, 9);
            }
            break;
        case 0:
            OBJ->vt->unk_08(OBJ);
            func_02016108(OBJ, func_0201c2a4(a, 4));
            func_ov052_02261908(a, 5);
            break;
        case 8:
            if (func_ov052_022610c4(OBJ) == 1 || func_ov052_022610c4(OBJ) == 2) {
                int *p = func_02095794(4);
                int rc;
                t[0] = p[0];
                t[1] = p[1];
                t[2] = p[2];
                rc = func_02030818(t);
                if (rc) {
                    func_020307f8(rc);
                } else {
                    func_ov052_02261908(a, 1);
                }
            } else if (func_ov052_022610c4(OBJ) == 0xc) {
                func_020b6098(func_020b5e10(), 0);
            } else {
                func_ov052_02261908(a, 1);
            }
            break;
    }
}
