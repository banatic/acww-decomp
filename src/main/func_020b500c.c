/* func_020b500c @ 0x020b500c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7c98(int, int);
extern int func_02050bdc_unk(int, int);
extern int func_020b4d70(int);
extern void func_020b512c(void *);

typedef struct UnkStruct_020b500c {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x14];
    int unk_3C;
    char pad_40[0x4];
    unsigned char unk_44;
    unsigned char unk_45;
    unsigned char unk_46;
    unsigned char unk_47;
    unsigned char unk_48;
} UnkStruct_020b500c;

void func_020b500c(UnkStruct_020b500c *p)
{
    unsigned char flag47;
    unsigned char flag48;
    void *obj;
    void **vt;
    int (*method)(void *);
    int v;

    flag47 = ((unsigned char *) p)[0x47];
    if (flag47 != 0) {
        obj = *(void **) ((char *) p->unk_24 + 0x18f0);
        vt = *(void ***) obj;
        method = ((int (**)(void *)) vt)[3];
        v = func_020a7c98(method(obj), 0);
        flag48 = ((unsigned char *) p)[0x48];
        if (flag48 != 0) {
            v = func_02050bdc_unk(v, flag48);
            ((unsigned char *) p)[0x48] = 0;
        }
        if (func_020b4d70(v) != 0) {
            p->unk_3C = v;
            func_020b512c(p);
            ((unsigned char *) p)[0x44] = 1;
        } else {
            ((unsigned char *) p)[0x45] = 0;
        }
    }
}
