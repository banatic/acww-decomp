/* func_02027d68 @ 0x02027d68, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int, void *);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    int word;
    unsigned char byte;
} UnkStruct_02027d68;
extern UnkStruct_02027d68 data_020c8978;

void func_02027d68(char *p1, char *p2)
{
    char *inner;
    int value;
    int local0, local1, local2, local3, local4;

    inner = *(char **) (p1 + 0x100);
    value = *(int *) (inner + 0x830);
    local0 = func_020036e8(func_0208150c(value, inner));
    local1 = data_020c8978.word;
    local2 = data_020c8978.byte;
    local3 = 0;
    local4 = 0;
    func_0202da38(p1, p1 + 0x104, p1 + 0x122, 30, local0, local1, local2, local3, local4);
    *(void **) p2 = p1 + 0x104;
    *(unsigned char *) (p2 + 4) = *(unsigned char *) (p1 + 0x122);
}
