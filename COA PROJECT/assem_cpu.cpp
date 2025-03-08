#include<bits/stdc++.h>
#include<fstream>
#include<cctype>
#include<unistd.h>

using namespace std;

vector<string> memory;
string convert_to_binary(const string &imm,int bit_length)
{
    unsigned int value =0;
    if(imm.find("0x")==0 || imm.find("0X")==0)
    {
        value=stoul(imm.substr(2),nullptr,16);
    }
    else if(imm.find("0b")==0 || imm.find("0B")==0)
    {
        value=stoul(imm.substr(2),nullptr,2);
    }
    else if(imm.find("-")==0 || imm.find("-")==0)
    {
        value=stoul(imm.substr(1),nullptr,10);
        cout<<value<<endl;
        int req=(int)value;
        cout<<req<<endl;
      string result= bitset<32>(req).to_string().substr(32-bit_length);
      cout<<result<<endl;
      bool flag=false;
      for(int i=bit_length-1;i>=0;i--)
      {
          if(!flag)
          {
              if(result[i]=='1')
              {
                  flag=true;
                //  cout<<flag<<" flag "<<i<<endl;
                  continue;
              }
          }
          if(flag)
          {
              //cout<<"state 2"<<endl;
              if(result[i]=='1')
              {
                  //cout<<"$"<<endl;
                  result[i]='0';
              }
              else
              {
                  //cout<<"$$"<<endl;
                  result[i]='1';
              }
          }
          cout<<i<<result<<endl;
      }
      cout<<result<<endl;
      return result;
    }
    else
    {
        value=stoul(imm,nullptr,10);
    }
    cout<<value<<endl;
    return bitset<32>(value).to_string().substr(32-bit_length);
}

class R_type
{
    public:
    string op;
    string operand;
    string opcode="0110011";
    string func3;
    string func7;
    string rd;
    string rs1;
    string rs2;
    string temp;
    string final;
    void read_op()
    {
        if(op=="ADD")
        {
            func3="000";
            func7="0000000";
        }
        else if(op=="SUB")
        {
            func3="000";
            func7="0100000";
        }
        else if(op=="SLL")
        {
            func3="001";
            func7="0000000";
        }
        else if(op=="XOR")
        {
            func3="100";
            func7="0000000";
        }
        else if(op=="SRL")
        {
            func3="101";
            func7="0000000";
        }
       else  if(op=="SRA")
        {
            func3="101";
            func7="0100000";
        }
       else  if(op=="OR")
        {
            func3="110";
            func7="0000000";
        }
       else  if(op=="AND")
        {
            func3="111";
            func7="0000000";
        }
       else if(op=="LR.D")
        {
            func3="011";
            func7="0001000";
        }
       else if(op=="SC.D")
        {
            func3="011";
            func7="0001100";
        }
        else if(op=="MUL")
       {
           func3="000";
           func7="0000001";
       }
       else if (op=="REM")
       {
           func3="000";
           func7="0000011";
       }
       else
        {
            cout<<"Invalid operand\n";
        }
       
      
    }
    void read_reg()
    {
    vector<string> token;
    stringstream check1(operand);
    string intermediate;
    while(getline(check1,intermediate,','))
    {
        token.push_back(intermediate);
       // cout<<intermediate<<endl;
    }
     for(int i=0;i<token.size();i++)
     {
         intermediate=token[i].substr(1);
       //  cout<<intermediate<<endl;
         unsigned int temp=stoi(intermediate);
       //  cout<<temp<<"--"<<endl;
         if(i==0)
         {
             rd=bitset<5>(temp).to_string();
       //     cout<<rd<<" rd "<<endl;
         }
         if(i==1)
         {
             rs1=bitset<5>(temp).to_string();
         //    cout<<rs1<<" rs1 "<<endl;
         }
         if(i==2)
         {
             rs2=bitset<5>(temp).to_string();
        //    cout<<rs2<<" rs2 "<<endl;
         }
     }
    }
   void concat()
    {
        final=func7+rs2+rs1+func3+rd+opcode;
    }
    
};

class I_type
{
    public :
    string op;
    string operand;
    string opcode="0010011";
    string func3;
    string rd;
    string rs1;
    string rs2;
    string imm;
    string func7;
    int flag=0;
    string final;
    
    void read_op()
    {
        if(op=="ADDI")
        {
            func3="000";
        }
        else if(op=="SLLI")
        { 
            func3="001";
            flag++;
            func7="0000000";
        }
        else if(op=="XORI")
        {
            func3="100";
        }
        else if(op=="SRLI")
        {
            func3="101";
            flag++;
            func7="0000000";
        }
        else if(op=="SRALI")
        {
            func3="101";
            flag++;
            func7="0100000";
        }
        else if(op=="ORI")
        {
            func3="110";
        }
        else if(op=="ANDI")
        {
            func3="111";
        }
        else if(op=="JALR")
        {
             func3="111";
             opcode="1100111";
        }
        else if(op=="LB")
        {
            opcode="0000011";
            func3="000";
        }
        else if(op=="LH")
        {
            opcode="0000011";
            func3="001";
        }
        else if(op=="Lw")
        {
            opcode="0000011";
            func3="010";
        }
        else if(op=="LBU")
        {
            opcode="0000011";
            func3="100";
        }
        else if(op=="LHU")
        {
            opcode="0000011";
            func3="101";
        }
    }
    void read_reg()
    {
        vector<string> token;
        stringstream check1(operand);
        string intermediate;
        while(getline(check1,intermediate,','))
        {
            token.push_back(intermediate);
            cout<<intermediate<<endl;
        }
        if(opcode=="0000011")
        {
             rs2=bitset<5>(stoi(token[0].substr(1))).to_string();
             string imm3;
             string rs;
             for(int i=0;i<token[1].size();i++)
             {
                if(token[1][i]=='(')
                {
                    
                    rs=token[1].substr(i+2,token[1].size()-1);
                    break;
                }
                imm3+=token[1][i];
             }
              rs1=bitset<5>(stoi(rs)).to_string();
              imm=convert_to_binary(imm3,12);           
        }
        else
        {
        for(int i=0;i<token.size();i++)
        {
         if(i==0 || i==1)
         intermediate=token[i].substr(1);
       //  cout<<intermediate<<endl;
        else
         intermediate=token[i];
         unsigned int temp=stoi(intermediate);
        // cout<<temp<<"--"<<endl;
         if(i==0)
         {
             rd=bitset<5>(temp).to_string();
           // cout<<rd<<" rd "<<endl;
         }
         if(i==1)
         {
             rs1=bitset<5>(temp).to_string();
          //  cout<<rs1<<" rs1 "<<endl;
         }
         if(i==2)
         {
             imm=convert_to_binary(token[i],12);
          //  cout<<imm<<" imm "<<endl;
         }
       }
        }
    }
    void concat()
    {
        if(opcode=="0000011")
        {
            final=imm.substr(0,7)+rs2+rs1+func3+imm.substr(7)+opcode;
            return;
        }
        final=imm+rs1+func3+rd+opcode;
    }
     
};

class U_type
{
    public:
    string op;
    string operand;
    string opcode;
    string rd;
    string imm;
    string final;
    
    void read_op()
    {
        if(op=="LUI")
        {
            opcode="0110111";
        }
        else if(op=="AUIPC")
        {
            opcode="0010111";
        }
    }
    
    void read_reg()
    {
         vector<string> token;
         stringstream check1(operand);
         string intermediate;
         getline(check1,intermediate,',');
         rd=bitset<5>(stoi(intermediate.substr(1))).to_string();
         getline(check1,intermediate,',');
         imm=convert_to_binary(intermediate,20);
    }
    
    void concat()
    {
        final = imm+rd+opcode;
    }
};


class B_type
{
    public:
    string op;
    string operand;
    string opcode="1100011";
    string imm;
    string func3;
    string rs1;
    string rs2;
    string  final;
    
    void read_op()
    {
        if(op=="BEQ")
        {
            func3="000";
        }
        else if(op=="BNE")
        {
            func3="001";
        }
        else if(op=="BLT")
        {
            func3="100";
        }
        else if(op=="BGE")
        {
            func3="101";
        }
        else if(op=="BLTU")
        {
            func3="110";
        }
        else if(op=="BGEU")
        {
            func3="111";
        }
    }
    
    void read_reg()
    {
        vector<string> token;
        stringstream check1(operand);
        string intermediate;
        while(getline(check1,intermediate,','))
        {
          token.push_back(intermediate);
         // cout<<intermediate<<endl;
        }
        rs1=bitset<5>(stoi(token[0].substr(1))).to_string();
        rs2=bitset<5>(stoi(token[1].substr(1))).to_string();
        imm=convert_to_binary(token[2],12);
    }
    
    void concat()
    {
        final=imm.substr(0,7)+rs2+rs1+func3+imm.substr(7,5)+opcode;
    }
};

class S_type
{
    public:
    string op;
    string operand;
    string opcode="0100011";
    string rs1;
    string rs2;
    string imm;
    string func3;
    string final;
    
    void read_op()
    {
        if(op=="SB")
        {
            func3="000";
        }
        else if(op=="SH")
        {
            func3="001";
        }
        else if(op=="SW")
        {
            func3="010";
        }
    }
    
    void read_reg()
    {
        vector<string> token;
        stringstream check1(operand);
        string intermediate;
        while(getline(check1,intermediate,','))
        {
          token.push_back(intermediate);
         // cout<<intermediate<<endl;
        }
           rs2=bitset<5>(stoi(token[0].substr(1))).to_string();
             string imm3;
             string rs;
             for(int i=0;i<token[1].size();i++)
             {
                if(token[1][i]=='(')
                {
                    
                    rs=token[1].substr(i+2,token[1].size()-1);
                    break;
                }
                imm3+=token[1][i];
             }
              rs1=bitset<5>(stoi(rs)).to_string();
              imm=convert_to_binary(imm3,12);
    }
    
    void concat()
    {
        final=imm.substr(0,7)+rs2+rs1+func3+imm.substr(7,5)+opcode;
    }
    
};


class J_type{
    public:
    string op;
    string operand;
    string opcode="1101111";
    string rd;
    string imm;
    string final;
    
     void read_reg()
    {
         vector<string> token;
         stringstream check1(operand);
         string intermediate;
         getline(check1,intermediate,',');
         rd=bitset<5>(stoi(intermediate.substr(1))).to_string();
         getline(check1,intermediate,',');
         imm=convert_to_binary(intermediate,20);
    }
    
    void concat()
    {
        final = imm+rd+opcode;
    }
};


class Decoder{
    public :
      void decode_instructions(const string& line ,ofstream &outfile)
      {
          vector<string> token;
          stringstream check(line);
          string intermediate;
          while(getline(check,intermediate,' '))
        {
          token.push_back(intermediate);
           cout<<intermediate<<endl;
        }
        
        if(token.size()<2) return;
        
        string op;
       
        for(int i=0;i<token[0].size();i++)
        {
            op.push_back(toupper(token[0][i]));
        }
        string operand=token[1];
        cout<<operand<<endl;
         cout<<op<<endl;
        if(op=="ADD"|| op=="SUB" || op=="SLL" || op=="XOR" || op=="SRL" || op=="SRA" || op=="OR" ||op=="AND" ||op=="MUL" ||op=="DIV" ||op=="REM")
        {
            R_type r;
            r.op=op;
            r.operand=operand;
            r.read_op();
            r.read_reg();
            r.concat();
            cout<<r.final<<endl;
            memory.push_back(r.final);
            outfile<<r.final<<endl;
        }
        else if(op=="ADDI"  || op=="SLLI" || op=="XORI" || op=="SRLI" || op=="SRAI" || op=="ANDI" || op=="JALR"||op=="LB")
        {
            I_type i;
            i.op=op;
            i.operand=operand;
            i.read_op();
            i.read_reg();
            i.concat();
            cout<<i.final<<endl;
            memory.push_back(i.final);
            outfile<<i.final<<endl;
        }
        else if(op=="LUI" || op=="AUIPC")
        {
            U_type u;
            u.op=op;
            u.operand=operand;
            u.read_op();
            u.read_reg();
            u.concat();
            cout<<u.final<<endl;
            memory.push_back(u.final);
            outfile<<u.final<<endl;
        }
        else if(op=="BEQ"||op=="BNE"||op=="BLT"||op=="BGE"||op=="BLTU"||op=="BGEU")
        {
            B_type b;
            b.op=op;
            b.operand=operand;
            b.read_op();
            b.read_reg();
            b.concat();
            cout<<b.final<<endl;
            memory.push_back(b.final);
            outfile<<b.final<<endl;
        }
        else if(op=="SB"|| op=="SH" || op=="SW")
        {
            S_type s;
            s.op=op;
            s.operand=operand;
            s.read_op();
            s.read_reg();
            s.concat();
            cout<<s.final<<endl;
            memory.push_back(s.final);
            outfile<<s.final<<endl;
        }
        else if(op=="JAL")
        {
            J_type j;
            j.op=op;
            j.operand=operand;
            j.read_reg();
            j.concat();
            cout<<j.final<<endl;
            memory.push_back(j.final);
            outfile<<j.final<<endl;
        }
        
      }
};

string to_upper(string str)
{
    transform(str.begin(),str.end(),str.begin(),::toupper);
    return str;
}
/*ASSEMBLER END HERE*/
/*CPU STARTS*/
struct G_P_R
{
    vector<long int>value=vector<long int>(32,0);
    vector<long int> ins=vector<long int>(32,0);
}GPR;

vector<long int > data_mem(1<<10,0);

enum ALUop{
    ADD,SUB,AND,OR,XOR,SLL,SRL,SLT,NO_OP,SRA,BEQ,BNE,BLT,BGE,BLTU,BGEU,MUL,LUI,AUIPC,REM
};

struct cw
{
 bool regread;
 bool regwrite;
 bool alusrc;
  bool aluop1;
  bool aluop2;
  bool branch;
  bool jump;
  bool memread;
  bool memwrite;
  bool memtoreg;
};

struct pipe1{
   long int pc;
    bool valid=true;
}p_counter;

struct pipe2{
  long  int DPC;
 long   int NPC;
    string IR;
    bool stall=false;
    bool valid=false;
}ifid;

struct pipe3{
 long int DPC;
 long int NPC;
 long int JPC;
 long int BPC;
 string opcode;
  struct cw ctrl;
 long int imm1;
 long int rs1;
 long int rs2;
 long int rsl2;
 long int imm2;
  string imm;
  string func3;
  string func7;
  string imm_branch;
 long int rdl;
  bool stall=false;
  bool valid=false;
}idex;

struct pipe4{
    struct cw ctrl;
  long  int aluout;
  long  int rs2;
  long  int rdl;
  long int  rsl2;
    bool stall=false;
    bool valid=false;
}exmo;

struct pipe5
{
    struct  cw ctrl;
  long int   ldout;
  long  int aluout;
  long  int rdl;
    bool stall=false;
    bool valid=false;
}mowb;


string find(string opcode)
{
    if(opcode=="0110011")
    {
        return "R";
    }
    else if(opcode=="0010011")
    {
        return "I";
    }
    else if(opcode=="0010111")
    {
        return "I";
    }
    else if(opcode=="1100011")
    {
        return "B";
    }
    else if(opcode=="0100011")
    {
        return "S";
    }
    else if(opcode=="1101111")
    {
        return "J";
    }
    else if(opcode=="0010111" || opcode=="0110111")
    {
        return "U";
    }
   return " ";
}
struct cw controller(string opcode,string func)
{
    cw control_word={0};
    string type=find(opcode);
    if(type=="R")
    {
        control_word.regread=true;
        control_word.regwrite=true;
        control_word.alusrc=false;
        control_word.aluop1=true;
        control_word.aluop2=false;
        control_word.branch=false;
        control_word.jump=false;
        control_word.memread=false;
        control_word.memwrite=false;
        control_word.memtoreg=false;
    }
    else if(type=="I")
    {
        control_word.regread=true;
        control_word.regwrite=true;
        control_word.alusrc=true;
        control_word.aluop1=true;
        control_word.aluop2=false;
        control_word.branch=false;
        control_word.jump=false;
        control_word.memread=false;
        control_word.memwrite=false;
        control_word.memtoreg=false; 
    }
    else if(type=="S")
    {
        control_word.regread=true;
        control_word.regwrite=false;
        control_word.alusrc=true;
        control_word.aluop1=true;
        control_word.aluop2=true;
        control_word.branch=false;
        control_word.jump=false;
        control_word.memread=false;
        control_word.memwrite=true;
        control_word.memtoreg=false;
    }
    else if(type=="B")
    {
        control_word.regread=true;
        control_word.regwrite=false;
        control_word.alusrc=false;
        control_word.aluop1=false;
        control_word.aluop2=true;
        control_word.branch=true;
        control_word.jump=false;
        control_word.memread=false;
        control_word.memwrite=false;
        control_word.memtoreg=false;
    }
    else if(type=="J")
    {
        control_word.regread=true;
        control_word.regwrite=true;
        control_word.alusrc=false;
        control_word.aluop1=true;
        control_word.aluop2=false;
        control_word.branch=false;
        control_word.jump=true;
        control_word.memread=false;
        control_word.memwrite=false;
        control_word.memtoreg=false;
    }
    else if(type=="U")
    {
        control_word.regread=true;
        control_word.regwrite=true;
        control_word.alusrc=true;
        control_word.aluop1=false;
        control_word.aluop2=false;
        control_word.branch=false;
        control_word.jump=false;
        control_word.memread=false;
        control_word.memwrite=false;
        control_word.memtoreg=false;
    }
    else
    {
        std::cerr<<"Invalid opcode"<<std::endl;
    }
    return control_word;
}
class fetch
{

public:
    int exe()
    {
        if(ifid.stall || !p_counter.valid)
        {
            return 0;
        }
        if(memory.size()<=p_counter.pc || p_counter.pc<0)
        {
            ifid.valid=false;
            return 0;
        }
        ifid.IR=memory[p_counter.pc];
        ifid.DPC=p_counter.pc;
        ifid.NPC=p_counter.pc+1;
        p_counter.pc=p_counter.pc+1;
        ifid.valid=true;
        cout<<"fetch done"<<endl;
        return 1;
    }
};

class decode
{
    public:
    string ir;
   long int dpc;
   long int npc;
    string opcode;
   long int rsl1;
   long int rsl2;
   long int rdl;
    
   public:
    int exe()
    {
        if(idex.stall || !ifid.valid)
        {
            idex.valid=false;
            return 0;
        }
        cout<<"Entering decode"<<endl;;
        ir=ifid.IR;
        dpc=ifid.DPC;
        npc=ifid.NPC;
        opcode=ir.substr(25,7);
        cout<<opcode<<endl;
        rsl1=stoul(ir.substr(12,5),nullptr,2);
        rsl2=stoul(ir.substr(7,5),nullptr,2);
        idex.rsl2=rsl2;
        rdl=stoul(ir.substr(20,5),nullptr,2);
        if(ir[0]=='0')
        {
        idex.JPC=ifid.NPC+((stoul(ir.substr(0,20),nullptr,2))/4);
        }
        else
        {
         idex.JPC=ifid.NPC+((-1*((1<<20)-stoul(ir.substr(0,20),nullptr,2))/4));
         
        }
        if(ir[0]=='0')
        {
           idex.BPC=npc+(stoul(ir.substr(0,7)+ir.substr(20,5),nullptr,2)/4);
        }
        else
        {
        idex.BPC=ifid.NPC-((4096-stoul(ir.substr(0,7)+ir.substr(20,5),nullptr,2))/4);
        cout<<ir.substr(0,7)<<ir.substr(20,5)<<endl;
                cout<<"BPC"<<idex.BPC<<"   "<<stoul(ir.substr(0,7)+ir.substr(20,5),nullptr,2)<<endl;
        }
        idex.DPC=ifid.DPC;
        idex.NPC=ifid.NPC;
        idex.imm=ir.substr(0,20);
        idex.func3=ir.substr(17,3);
        idex.func7=ir.substr(0,7);
        idex.opcode=opcode;
        idex.rdl=rdl;
      idex.ctrl= controller(opcode,idex.func3);
      cout<<"decode middle"<<rdl<<" "<<rsl1<<" "<<rsl2<<" "<<endl;
      if(idex.ctrl.regread)
      {
          if(GPR.ins[rsl1]==0 || rsl1==0)
          {
              idex.rs1=GPR.value[rsl1];
              cout<<idex.rs1;
          }
          else
          {
              ifid.stall =true;
              idex.valid=false;
              cout<<"***"<<endl;
              return 0;
          }
      }
      if(idex.ctrl.alusrc)
      {
          if(idex.ctrl.regread)
          {
              if(opcode=="0110111")
                 {
                     idex.rs2=stoul(ir.substr(0,20),nullptr,2);
                 }
              if(opcode=="0100011")
              {
                 idex.rs2=stoul(ir.substr(0,7)+ir.substr(20,5),nullptr,2);
   
              }
               else
              idex.rs2=stoul(ir.substr(0,12),nullptr,2);
              cout<<"I"<<idex.rs2<<endl;
          }
      }
      else
      {
          if(idex.ctrl.regread)
          {
              if(GPR.ins[rsl2]==0 || rsl2==0)
              {
                  idex.rs2=GPR.value[rsl2];
              }
              else
              {
                  ifid.stall=true;
                  idex.valid=false;
                  cout<<"**"<<endl;
                  return 0;
              }
          }
      }
      GPR.ins[idex.rdl]=1;
      ifid.stall=false;
      idex.valid=true;
      cout<<"decode done"<<rdl<<" "<<rsl1<<" "<<rsl2<<" "<<" "<<idex.func3<<" "<<idex.func7<<endl;
      return 1;
    }
};


ALUop ALUcontrol(bool aluop1,bool aluop2,string func3,string func7,string opcode)
{
    if(aluop1==true && aluop2==false)
    {
        if(func3=="000" )
        {
            if(func7=="0100000")
            return SUB;
            else if(func7=="0000000")
            return ADD;
            else if(func7=="0000001")
            return MUL;
            else if(func7=="0000011")
            return REM;
            return ADD;
        }
        else if(func3=="001" )
        {
            return SLL;
        }
        else if(func3=="100")
        {
            return XOR;
        }
        else if(func3=="101" )
        {
            return SRL;
        }
        else if(func3=="101" )
        {
            return SRA;
        }
        else if(func3=="110" )
        {
            return OR;
        }
        else if(func3=="111" )
        {
            return AND;
        }
        /*else if(func3=="011" && func7=="0001000")
        {
            return LR.D;
        }
        else if(func3=="011" && func7=="0001100")
        {
            return SC.D;
        }*/
     }
    else if(aluop1==false && aluop2==true)
    {
        if(func3=="000")
        {
            return BEQ;
        }
        else if(func3=="001")
        {
            return BNE;
        }
        else if(func3=="100")
        {
            return BLT;
        }
        else if(func3=="101")
        {
            return BGE;
        }
        else if(func3=="110")
        {
            return BLTU;
        }
        else if(func3=="111")
        {
            return BGEU;
        }
    }
    else if(aluop1==false && aluop2==false)
    {
      if(opcode=="0110111")
      {
          return LUI;
      }
      else if(opcode=="0010111")
      {
         return AUIPC;
      }
    }
    else{
        return ADD;
    }
    return NO_OP;
    
}

bool FLAG_check(int s1,int s2)
{
    return s1==s2;
}

int ALU(ALUop alusel,int s1,int s2)
{
    switch(alusel)
    {
        case ADD : return s1+s2;
        case SUB:  return s1-s2;
        case AND: return  s1&s2;
        case OR: return s1|s2;
        case XOR: return s1^s2;
        case SLL : return s1<<(s2&0x1F);
        case SRL: return (unsigned int)s1>>(s2&0x1F);
        case SRA: return s1>>(s2&&0x1F);
        case SLT: return s1<s2?1:0;
        case BEQ:
                 {
                    if(s1==s2) return 1;
                    else return 0;
                 }
        case BNE:
                 {
                    if(s1!=s2) return 1;
                    else return 0;
                 }
        case BLT:
                 {
                    if(s1<s2) return 1;
                    else return 0;
                 }
        case BGE:
                 {
                    if(s1>=s2) return 1;
                    else return 0;
                 }
        case BLTU:
                {
                    if((unsigned int)s1<(unsigned int)s2) return 1;
                    else return 0;
                 }
        case BGEU:
                {
                    if((unsigned int)s1>=(unsigned int)s2) return 1;
                    else return 0;
                 }
        case LUI:
                {
                    return s2<<12;
                }
        case AUIPC:
                {
                    return p_counter.pc+((s2<<12)/4);
                }
        case MUL:
                {
                    return s1*s2;
                }
        case REM:
                {
                     return s1%s2;
                }
        return 0;
    }
    return 0;
}

class execute
{
  ALUop ALUselect;
  bool ALUflag;
  
 public:
  int exe()
  {
      if(exmo.stall || !idex.valid)
      {
          exmo.valid=false;
          return 0;
      }
      ALUselect=ALUcontrol(idex.ctrl.aluop1,idex.ctrl.aluop2,idex.func3,idex.func7,idex.opcode);
      exmo.aluout=ALU(ALUselect,idex.rs1,idex.rs2);
     // ALUflag=FLAG_check(ALUselect,idex.rs1,idex.rs2);
      exmo.ctrl=idex.ctrl;
      if(idex.ctrl.branch)
      {
          if(exmo.aluout)
          {
             cout<<"branching"<<endl;
              p_counter.pc=idex.BPC;
              ifid.valid=false;
              idex.valid=false;
              cout<<"branch"<<" "<<p_counter.pc<<endl;
            //  sleep(2);
            //  p_counter.valid=false;
          }
      }
      if(idex.ctrl.jump)
      {
              p_counter.pc=idex.JPC;
              
              ifid.valid=false;
              idex.valid=false;
              cout<<"jump"<<" "<<p_counter.pc<<endl;
           //   p_counter.valid=false;
      }
      exmo.rs2=idex.rs2;
      exmo.rdl=idex.rdl;
      exmo.rsl2=idex.rsl2;
      idex.stall=false;
      exmo.valid=true;
      cout<<"exeute done "<<ALUselect<<endl;
      return 1;
  }
};

class memoryaccess
{
 public:
    int exe()
    {
        if(mowb.stall || !exmo.valid)
        {
            mowb.valid=false;
            return 0;
        }
        cout<<"entering memory access"<<endl;
        cout<<exmo.ctrl.memwrite<<endl;
         cout<<exmo.rs2<<" "<<exmo.aluout<<endl;
        if(exmo.ctrl.memwrite)
        {
            data_mem[exmo.aluout]=GPR.value[exmo.rsl2];
            cout<<exmo.rs2<<" "<<exmo.aluout<<endl;

        }
        if(exmo.ctrl.memread)
        {
            mowb.ldout=data_mem[exmo.aluout];
        }
        mowb.aluout=exmo.aluout;
        mowb.rdl=exmo.rdl;
        mowb.valid=true;
        exmo.stall=false;
        mowb.ctrl=exmo.ctrl;
        cout<<"exiting memory_access"<<endl;
        return 1;
    }
};


class register_write
{
 public:
    int exe()
    {
        if(!mowb.valid)
        {
            return 0;
        }
        cout<<"entering register_write"<<endl;
        cout<<mowb.ctrl.regwrite<<endl;
        cout<<"ldout"<<mowb.aluout<<endl;
        if(!mowb.ctrl.regwrite)
        {
            return 0;
        }
        else if(mowb.ctrl.memtoreg && GPR.ins[mowb.rdl]==1)
        {
            GPR.value[mowb.rdl]==mowb.ldout;
        }
        else
        {
            GPR.value[mowb.rdl]=mowb.aluout;
            cout<<"register write"<<mowb.rdl<<" "<<mowb.aluout<<endl;
        }
        GPR.ins[mowb.rdl]=0;
        mowb.stall=false;
        return 1;
    }
};





int main()
{
    /*
    string ins1="sub x1,x2,x3";
    R_type r;
    vector<string> token;
    stringstream check1(ins1);
    string intermediate;
    while(getline(check1,intermediate,' '))
    {
        token.push_back(intermediate);
    }
    string upper;
    for(int i=0;i<token[0].size();i++)
    {
        upper.push_back(toupper(token[0][i]));
    }
    cout<<upper<<endl;
    r.op=upper;
    r.operand=token[1];
    r.read_op();
    cout<<r.opcode<<endl<<r.func3<<endl<<r.func7<<endl;
    r.read_reg();
    r.concat();
    cout<<r.final<<endl;
   return 0; */
   /*
    string ins1="addi x1,x2,23";
    I_type i;
    vector<string> token;
    stringstream check1(ins1);
    string intermediate;
    while(getline(check1,intermediate,' '))
    {
        token.push_back(intermediate);
    }
    string upper;
    for(int i=0;i<token[0].size();i++)
    {
        upper.push_back(toupper(token[0][i]));
    }
   // cout<<upper<<endl;
    i.op=upper;
    i.operand=token[1];
    i.read_op();
   // cout<<i.opcode<<endl<<i.func3<<endl;
    i.read_reg();
    i.concat();
    cout<<i.final<<endl;
   return 0;*/
   int n;
   cin>>n;
    ifstream infile;
   if(n==1)
  infile.open("b.s");
   else
  infile.open("a.s");
   
   ofstream outfile("file.txt");
   Decoder decoder;
   string line;
   while(getline(infile,line))
   {
       decoder.decode_instructions(line,outfile);
       cout<<line<<endl;
   }
   
   infile.close();
   outfile.close();

   for(int i=0; i<memory.size(); i++)
   {
    cout<<i<<"  "<<memory[i]<<endl;
   }
  //  GPR.value[1]=10;
   // GPR.value[2]=22;
   cout<<"---------------------------------------------------------------------------"<<endl;
   cout<<"                    Assembler ends ....Running instructions on CPU         "<<endl;
   cout<<"---------------------------------------------------------------------------"<<endl;
   cout<<"         Fetch -> Decode -> Execute -> Memory Access -> Register Write     "<<endl;
   cout<<"---------------------------------------------------------------------------"<<endl;
   sleep(1);
   p_counter.valid=true;

    p_counter.pc=0;
    fetch f;
    decode d;
    execute e;
    memoryaccess m;
    register_write re;
    long int clk=0;
    while(1)
    {
        clk++;
        cout<<"================================================================================================"<<endl;
        int reg_return=re.exe();
        cout<<"______________register_write "<<reg_return<<endl;
        int memor_return=m.exe();
        cout<<"______________memor_return  "<<memor_return<<endl;
        int execute_return=e.exe();
        cout<<"______________execute_Return "<<execute_return<<endl;
        int decode_return=d.exe();
        cout<<"______________decode_return  "<<decode_return<<endl;
        int fetch_return=f.exe();
        cout<<"______________fetch_return  "<<fetch_return<<"     "<<p_counter.pc-1<<endl;
        cout<<"============================================================================================"<<endl;
        if(!reg_return && !memor_return && !execute_return && !decode_return && !fetch_return)
        {
            break;
        }
    }
    for(int i=0;i<32;i++)
    {
        cout<<"GPR value "<<i<<" "<<GPR.value[i]<<endl;
    }
    cout<<GPR.value[5]<<" "<<GPR.value[4]<<" "<<GPR.value[1]<<" "<<GPR.value[2]<<" "<<endl;
    cout<<"================================================================"<<endl;
    cout<<data_mem[0]<<endl;
    cout<<"clock"<<clk<<endl;
    return 0;
}