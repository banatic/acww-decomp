/* func_0202b770 @ 0x0202b770, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *p);
extern int func_02081d20(void);
extern int func_0207a650(void *a, void *b);
extern void func_0208150c(int val);
extern int func_020036e8(void);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern void func_0202da88(void *a, void *b);

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202b770_3;

typedef struct {
    char pad_00[0x100];
    UnkStruct_0202b770_3 *unk_100;
    char unk_104[0x1e];
    char unk_122[0x0a];
    int unk_12C;
} UnkStruct_0202b770;

typedef struct {
    int word;
    unsigned char byte;
} UnkStruct_0202b770_2;

extern UnkStruct_0202b770_2 data_020c8b20;
extern char data_021e5a2c;
extern char data_021c2794;

int func_0202b770(UnkStruct_0202b770 *p)
{
    int local;
    func_0209df64(&local);
    if (p->unk_12C == 0) {
        goto fail;
    }
    if (func_02081d20() < 0) {
        goto fail;
    }
    if (func_0207a650(&data_021e5a2c, &local) == 0) {
        goto fail;
    }
    func_0208150c(p->unk_100->unk_830);
    func_0202da38(p, p->unk_104, p->unk_122, 30, func_020036e8(), data_020c8b20.word, data_020c8b20.byte, 0, 0);
    func_0202da88(p, &data_021c2794);
    return 1;
fail:
    return 0;
}
