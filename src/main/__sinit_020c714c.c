/* __sinit_020c714c @ 0x020c714c, 0x1d4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_020c714c;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020c714c_2;
extern void __register_global_object(void *, void *, void *);
extern void func_020012dc(void *);
extern UnkStruct_020c714c_2 data_021fbcc0[2];
extern int data_021fbca8, data_021fbcb4;
extern char data_021fbc98[4];
extern char data_021fbca4[4];
extern char data_021fbc9c[4];
extern char data_021fbc8c[4];
extern char data_021fbc90[4];
extern char data_021fbc94[4];
extern UnkStruct_020c714c data_021fbcd8[16];
extern UnkStruct_020c714c data_020e7d78;
extern UnkStruct_020c714c data_020e7d80;
extern UnkStruct_020c714c data_020e7da8;
extern UnkStruct_020c714c data_020e7da0;
extern UnkStruct_020c714c data_020e7d98;
extern UnkStruct_020c714c data_020e7d20;
extern UnkStruct_020c714c data_020e7d88;
extern UnkStruct_020c714c data_020e7d18;
extern UnkStruct_020c714c data_020e7d30;
extern UnkStruct_020c714c data_020e7d38;
extern UnkStruct_020c714c data_020e7d68;
extern UnkStruct_020c714c data_020e7d40;
extern UnkStruct_020c714c data_020e7d48;
extern UnkStruct_020c714c data_020e7d50;
extern UnkStruct_020c714c data_020e7d58;
extern UnkStruct_020c714c data_020e7d60;
extern UnkStruct_020c714c data_021fbd58[4];
extern UnkStruct_020c714c data_020e7d70;
extern UnkStruct_020c714c data_020e7d90;
extern UnkStruct_020c714c data_020e7d28;
extern UnkStruct_020c714c data_020e7d10;

void __sinit_020c714c(void)
{
    UnkStruct_020c714c_2 *p;
    data_021fbc98[0] = 0x1f;
    data_021fbc98[1] = 0x14;
    data_021fbc98[2] = 0x14;
    data_021fbc98[3] = 0x1f;
    data_021fbca4[0] = 0x14;
    data_021fbca4[1] = 0x14;
    data_021fbca4[2] = 0x1f;
    data_021fbca4[3] = 0x1f;
    data_021fbc9c[0] = 0x1f;
    data_021fbc9c[1] = 0x1f;
    data_021fbc9c[2] = 0x14;
    data_021fbc9c[3] = 0x1f;
    data_021fbc8c[0] = 0x14;
    data_021fbc8c[1] = 0x1f;
    data_021fbc8c[2] = 0x14;
    data_021fbc8c[3] = 0x1f;
    data_021fbc90[0] = 0x14;
    data_021fbc90[1] = 0x1f;
    data_021fbc90[2] = 0x1f;
    data_021fbc90[3] = 0x1f;
    data_021fbc94[0] = 0x14;
    data_021fbc94[1] = 0x18;
    data_021fbc94[2] = 0x18;
    data_021fbc94[3] = 0x1f;
    data_021fbcd8[0] = data_020e7d78;
    data_021fbcd8[1] = data_020e7d80;
    data_021fbcd8[2] = data_020e7da8;
    data_021fbcd8[3] = data_020e7da0;
    data_021fbcd8[4] = data_020e7d98;
    data_021fbcd8[5] = data_020e7d20;
    data_021fbcd8[6] = data_020e7d88;
    data_021fbcd8[7] = data_020e7d18;
    data_021fbcd8[8] = data_020e7d30;
    data_021fbcd8[9] = data_020e7d38;
    data_021fbcd8[10] = data_020e7d68;
    data_021fbcd8[11] = data_020e7d40;
    data_021fbcd8[12] = data_020e7d48;
    data_021fbcd8[13] = data_020e7d50;
    data_021fbcd8[14] = data_020e7d58;
    data_021fbcd8[15] = data_020e7d60;
    data_021fbd58[0] = data_020e7d70;
    data_021fbd58[1] = data_020e7d90;
    data_021fbd58[2] = data_020e7d28;
    data_021fbd58[3] = data_020e7d10;
    p = &data_021fbcc0[0];
    p->a = 0x800;
    p->b = 0;
    p->c = 0x1000;
    __register_global_object((void *) (p), (((void *) func_020012dc)), (void *) (&data_021fbca8));
    p = &data_021fbcc0[1];
    p->a = -0x800;
    p->b = 0;
    p->c = 0x1000;
    __register_global_object((void *) (p), (((void *) func_020012dc)), (void *) (&data_021fbcb4));
}
