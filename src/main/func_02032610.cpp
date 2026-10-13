/* func_02032610 @ 0x02032610, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" long long func_01ffd028(void *, int);

class Node {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void virt(int, int, int);
    unsigned char pad_04[0x34];
    Node *next; // 0x38
    unsigned char pad_3C[0xc];
    int unk_48; // 0x48
};

extern Node *data_021c30e0;

extern "C" void func_02032610(int arg0, int arg1, int arg2)
{
    Node *node = data_021c30e0;
    if (node) {
        while (node) {
            long long result = func_01ffd028((char *) node + 0x3c, arg0);
            if (node->unk_48 >= result) {
                node->virt(arg0, arg2, arg1);
            }
            node = node->next;
        }
    }
}
