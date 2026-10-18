/* Execute original scheduler/PMF bodies and observe SP at every actual call. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arm.h"
#include "memory.h"
#include "member_frames_rom.h"
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"Failed %d: %s owner %08x mode %u\n",__LINE__,#x,owner->address,mode); exit(2); } } while(0)
#define SELF 0x023c0000u
#define NODE 0x023c1000u
#define OBJ 0x023c4000u
#define VT 0x023c8000u
#define CB 0x023e0000u
#define STACK 0x023f0000u
static const struct Owner *owner;
static unsigned mode, count, cases, total_calls, frame_bias;
static int adjustment[3], result_a, result_b;
static uint32_t packed[7];
static uint32_t word(uint32_t at) { return *(uint32_t *)(uintptr_t)at; }
static void put(uint32_t at,uint32_t value) { *(uint32_t *)(uintptr_t)at=value; }
static int callback(ArmCpu *cpu,void *user)
{
    uint32_t at=(uint32_t)(uintptr_t)user;
    CHECK(cpu->r[13]==STACK-owner->extent-frame_bias);
    uint32_t result=0x76543210;
    switch(owner->address) {
    case 0x020ee934: CHECK(at==(mode&1 ? 0x020ee964u : 0x020ee9a0u)); break;
    case 0x020ee964: CHECK(at==0x020ee834 && word(0x0213e7fc)==5); break;
    case 0x020ee9a0: {
        static const unsigned flags[]={4,2,3,5,1};
        CHECK(count<5 && at==(count==4 ? 0x020eea4cu : 0x020ee834u));
        CHECK(word(0x0213e7fc)==flags[count]); break;
    }
    case 0x020ee834: CHECK(at==CB && cpu->r[0]==OBJ); break;
    case 0x020eea4c:
        if(at==0x01ffcffc) {
            CHECK(cpu->r[0]>=NODE && cpu->r[0]<NODE+0x80);
            result=word(cpu->r[0]+4);
        } else { CHECK(at==CB && cpu->r[0]==OBJ); }
        break;
    case 0x01ffd14c:
        CHECK(at==0x01ffd44c);
        for(unsigned i=0;i<7;i++) CHECK((i<4 ? cpu->r[i] : word(cpu->r[13]+(i-4)*4))==packed[i]);
        break;
    case 0x01ffd44c: {
        unsigned which=(at-CB)/4;
        CHECK(at>=CB && at<CB+12 && (at-CB)%4==0);
        CHECK(cpu->r[0]==OBJ+(uint32_t)adjustment[which]);
        CHECK(which==(count==0 ? 1u : count==1 && result_b ? 0u : 2u));
        if(which==1) result=(uint32_t)result_b;
        if(which==0) result=(uint32_t)result_a;
        if(which==2) CHECK(cpu->r[1]==(result_b==0 ? 0u : result_a==-1 ? 3u : result_a==1 ? 2u : 1u));
        break;
    }
    default: CHECK(0);
    }
    count++; total_calls++;
    cpu->r[0]=result;
    cpu->r[1]=0xaaaaaaaa; cpu->r[2]=0xbbbbbbbb; cpu->r[3]=0xcccccccc; cpu->r[12]=0xdddddddd;
    cpu->r[15]=cpu->r[14]&~1u;
    if(cpu->r[14]&1) cpu->cpsr|=ARM_CPSR_T; else cpu->cpsr&=~ARM_CPSR_T;
    return 0;
}
static ArmHook hooks(void *user,uint32_t at,void **hook_user)
{
    (void)user;
    if(at>=owner->address && at<owner->address+owner->size) return NULL;
    *hook_user=(void *)(uintptr_t)at;
    return callback;
}
int main(int argc, char **argv)
{
    unsigned poisoned=argc==2 ? (unsigned)strtoul(argv[1],NULL,10) : ~0u;
    owner=&owners[0];
    CHECK(memory_init()==0);
    for(unsigned n=0;n<sizeof(owners)/sizeof(owners[0]);n++) {
        owner=&owners[n];
        frame_bias=n==poisoned ? 4u : 0u;
        memcpy((void *)(uintptr_t)owner->address,owner->code,owner->size);
        unsigned calls_before=total_calls;
        for(mode=0;mode<64;mode++) {
            memset((void *)(uintptr_t)SELF,0,0x9000);
            memset((void *)(uintptr_t)(STACK-256),0xcc,320);
            ArmCpu cpu; arm_init(&cpu); cpu.hook_at=hooks;
            cpu.r[0]=SELF; cpu.r[13]=STACK;
            for(unsigned r=4;r<=11;r++) cpu.r[r]=0x55000000+r;
            unsigned nodes=mode<2 ? 0 : 1+mode%4;
            int adj=(int[]){-8,0,12}[mode%3];
            if(owner->address==0x020ee934) cpu.r[0]=mode&1;
            if(owner->address==0x020ee834 || owner->address==0x020eea4c) {
                unsigned pmf=owner->address==0x020ee834 ? 8 : 4;
                put(SELF,mode==1 ? 0 : NODE);
                put(SELF+pmf,mode==0 ? 0 : mode&1 ? 8 : CB|1);
                put(SELF+pmf+4,mode==0 ? 0 : (uint32_t)adj*2+(mode&1));
                put(OBJ,VT); put(VT+8,CB|1);
                for(unsigned i=0;i<nodes;i++) {
                    put(NODE+i*0x20+4,i+1<nodes ? NODE+(i+1)*0x20 : 0);
                    put(NODE+i*0x20+(pmf==8 ? 8 : 16),OBJ-(uint32_t)adj);
                }
            }
            if(owner->address==0x01ffd14c) {
                static const unsigned addresses[]={0x01ffd0cc,0x01ffd0d4,0x01ffd0b4};
                packed[0]=SELF;
                for(unsigned i=0;i<6;i++) {
                    packed[i+1]=0x80000001u+mode*257+i*0x10000;
                    put(addresses[i/2]+(i%2)*4,packed[i+1]);
                }
            }
            if(owner->address==0x01ffd44c) {
                packed[0]=OBJ;
                result_a=(int[]){-1,0,1,7}[mode>>4]; result_b=(mode>>3)&1;
                for(unsigned i=0;i<3;i++) {
                    unsigned virt=(mode>>i)&1;
                    adjustment[i]=(int[]){-8,0,12}[(mode+i)%3];
                    packed[1+i*2]=virt ? i*4 : (CB+i*4)|1;
                    packed[2+i*2]=(uint32_t)adjustment[i]*2+virt;
                    put(OBJ+(uint32_t)adjustment[i],VT); put(VT+i*4,(CB+i*4)|1);
                }
                for(unsigned i=0;i<7;i++) {
                    if(i<4) cpu.r[i]=packed[i]; else put(STACK+(i-4)*4,packed[i]);
                }
            }
            count=0;
            CHECK(arm_call(&cpu,owner->address,10000)==ARM_RETURNED);
            CHECK(cpu.r[13]==STACK);
            for(unsigned r=4;r<=11;r++) CHECK(cpu.r[r]==0x55000000+r);
            unsigned expected=1;
            if(owner->address==0x020ee9a0) expected=5;
            if(owner->address==0x020ee834 || owner->address==0x020eea4c) {
                expected=nodes*(owner->address==0x020eea4c ? 2 : 1);
                CHECK(cpu.r[0]==1);
            }
            if(owner->address==0x01ffd44c) {
                expected=result_b ? 3 : 2;
                CHECK(cpu.r[0]==(uint32_t)(result_b ? result_a : 0));
            }
            CHECK(count==expected);
            cases++;
        }
        printf("%08x: 64 actual ARM cases, %u calls at SP - %u, balanced returns\n",owner->address,total_calls-calls_before,owner->extent);
    }
    CHECK(cases==448 && total_calls>1000);
    printf("%u original ARM frame cases, %u call boundaries; both scheduler branches, null/empty lists, direct/virtual PMFs, signed adjustments and all dispatcher outcomes\n",cases,total_calls);
    return 0;
}
