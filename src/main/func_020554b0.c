/* func_020554b0 @ 0x020554b0, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020554b0 UnkStruct_020554b0;
struct UnkStruct_020554b0 {
    unsigned char unk_00[0x5c];
    void *unk_5C;
};

extern void *func_02107828(void *);
extern void *func_021077e8(void *);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);
extern void func_02055f6c(UnkStruct_020554b0 *);

void func_020554b0(UnkStruct_020554b0 *that, void *arg2)
{
    char *list;
    char *node;
    void *other;
    unsigned short offset;
    unsigned int node_offset;

    list = (char *) func_02107828(arg2);
    offset = *(unsigned short *) (list + 0xe);
    node_offset = *(unsigned int *) (list + offset + 0xc);
    node = list + node_offset;
    other = func_021077e8(arg2);
    that->unk_5C = node;
    NNS_G3dBindMdlTex(that->unk_5C, other);
    NNS_G3dBindMdlPltt(that->unk_5C, other);
    func_02055f6c(that);
}
