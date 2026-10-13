/* func_0207cf14 @ 0x0207cf14, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned char unk_02[12];
    unsigned char pad_0E;
    unsigned char unk_0F;
} UnkStruct_0207cf14;

typedef struct {
    unsigned char data[0x7ec];
} BigStruct;

extern int func_02003704(UnkStruct_0207cf14 *obj);
extern UnkStruct_0207cf14 *func_0208150c(BigStruct *p);
extern int memcmp(const void *s1, const void *s2, int n);

int func_0207cf14(BigStruct *base, UnkStruct_0207cf14 *obj)
{
    int result = -1;
    if (func_02003704(obj)) {
        int i;
        for (i = 0; i < 8; i++) {
            UnkStruct_0207cf14 *p = func_0208150c(&base[i]);
            if (obj->unk_00 == p->unk_00 && memcmp(&obj->unk_02, &p->unk_02, 12) == 0 && obj->unk_0F == p->unk_0F) {
                result = i;
                break;
            }
        }
    }
    return result;
}
