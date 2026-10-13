/* func_02070cc4 @ 0x02070cc4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Identity43_(void *buf);
extern void MTX_Concat43(void *buf, void *arg1, void *arg2);
extern unsigned int data_021cfe68;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02070cc4;

void func_02070cc4(UnkStruct_02070cc4 *src)
{
    unsigned int buf[12];
    MTX_Identity43_(buf);
    buf[9] = src->unk_00;
    buf[10] = src->unk_04;
    buf[11] = src->unk_08;
    MTX_Concat43(buf, &data_021cfe68, &data_021cfe68);
}
