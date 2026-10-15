/* func_020207b8 @ 0x020207b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(void *p);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *a1, void *a2, void *a3, int a4, int a5, int a6, int a7, int a8, int a9);

typedef struct {
    int word;
    unsigned char byte;
} UnkStruct_020207b8;

extern UnkStruct_020207b8 data_020c8ab0;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    void *unk_104;
    char pad_108[0x122 - 0x108];
    unsigned char unk_122;
} UnkStruct_020207b8_2;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020207b8_3;

void func_020207b8(UnkStruct_020207b8_2 *s, UnkStruct_020207b8_3 *out)
{
    int result;
    int g_word;
    unsigned char g_byte;

    result = func_020036e8((unsigned char *) func_0208150c(*(void **) ((char *) s->unk_100 + 0x830)));
    g_word = data_020c8ab0.word;
    g_byte = data_020c8ab0.byte;

    func_0202da38(s, &s->unk_104, &s->unk_122, 0x1e, result, g_word, 1, 0x14, g_byte);

    out->ptr = &s->unk_104;
    out->byte = s->unk_122;
}
