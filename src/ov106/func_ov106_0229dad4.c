/* func_ov106_0229dad4 @ 0x0229dad4, 0x130 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O1,s
 */

extern int func_0206f56c(void *);
extern void func_ov106_0229cc50(void *);
extern void func_ov106_0229d3bc(void *);
extern int func_ov002_02208014(void *);
extern void func_ov106_0229d724(void *);
extern void func_ov106_0229d3e8(void *);
extern void func_ov002_0220a1dc(void *);
extern void func_ov002_02208098(void *, int);
extern int func_ov002_02208008(void *);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov106_0229cba8(void *, int, int);
extern struct {
    char pad[2];
    unsigned short flags;
} data_021fbe40;

void func_ov106_0229dad4(void *p)
{
    if (func_0206f56c(p)) {
        func_ov106_0229cc50(p);
        func_ov106_0229d3bc(p);
    } else if (func_ov002_02208014(p)) {
        func_ov106_0229d724(p);
    } else if (data_021fbe40.flags & 1) {
        func_ov002_0220a1dc((char *) p + 0x22a0);
        func_ov002_02208098(p, 0x1e);
    } else if (data_021fbe40.flags & 2) {
        func_ov106_0229cc50(p);
        func_ov106_0229d3bc(p);
    } else if (data_021fbe40.flags & 8) {
        func_ov106_0229cc50(p);
        func_ov106_0229d3e8(p);
    } else {
        unsigned char init = *(unsigned char *) ((char *) p + 0xbe);
        int res = func_ov002_02208008(p);
        if (func_ov002_022088ac(res)) {
            if (*(unsigned char *) ((char *) p + 0xbe) != 0) {
                (*(unsigned char *) ((char *) p + 0xbe))--;
            }
        } else if (func_ov002_0220889c(res)) {
            if (*(unsigned char *) ((char *) p + 0xbe) < 1) {
                (*(unsigned char *) ((char *) p + 0xbe))++;
            }
        }
        if (init != *(unsigned char *) ((char *) p + 0xbe)) {
            if (*(unsigned char *) ((char *) p + 0xbe) != 0) {
                int v1 = func_ov002_0220a768((char *) p + 0x3fb4, 4);
                int v2 = func_ov002_0220a72c((char *) p + (0x3fb4 + 0), 4);
                func_ov106_0229cba8(p, v1, v2);
            } else {
                int v1 = func_ov002_0220a768((char *) p + 0x3fb4, 3);
                int v2 = func_ov002_0220a72c((char *) p + (0x3fb4 + 0), 3);
                func_ov106_0229cba8(p, v1, v2);
            }
        }
    }
}
