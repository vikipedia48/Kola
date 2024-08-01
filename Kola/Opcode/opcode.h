#ifndef OPCODE_H
#define OPCODE_H

#include <QString>

#include "../Model/model.h"

class Opcode
{
public:
    static std::unique_ptr<Opcode> fromName(const QString& name);
    virtual QString name() = 0;
    virtual QString description() = 0;
    virtual std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) = 0;
    virtual uint32_t pushSize() { return 0; }
    virtual uint32_t swapSize() { return 0; }
    virtual uint32_t dupSize() { return 0; }
    virtual std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) { return std::nullopt; }
    virtual bool isPush() { return false; }
    virtual bool editsMemory() { return false; }
    virtual bool isSStore() { return false; }
    virtual bool isSLoad() { return false; }
    virtual bool isCallDataLoad() { return false; }
    virtual bool isCallDataCopy() { return false; }
    virtual bool isCallDataSize() { return false; }
    virtual QString callsContract(const std::vector<QString>& stack, QString arg = {}) { return {}; }
    virtual bool decreasesDepth() { return false; }
    virtual Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) { return {}; };
    virtual bool pushesNewValue() { return true; }

};

class Unknown : public Opcode {
    QString name() override { return "?"; }
    QString description() override { return "this opcode is supported by EVM, but not by Kola"; }
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override { return {}; }
    bool pushesNewValue() override { return false; }
};

class Invalid : public Opcode {
    QString name() override { return "INVALID"; }
    QString description() override;
    bool decreasesDepth() override { return true; }
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};

class Stop : public Opcode {
    QString name() override { return "STOP"; }
    QString description() override;
    bool decreasesDepth() override { return true; }
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};

class Add : public Opcode {
    QString name() override { return "ADD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Mul : public Opcode {
    QString name() override { return "MUL"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Sub : public Opcode {
    QString name() override { return "SUB"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Div : public Opcode {
    QString name() override { return "DIV"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class SDiv : public Opcode {
    QString name() override { return "SDIV"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Mod : public Opcode {
    QString name() override { return "MOD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class SMod : public Opcode {
    QString name() override { return "SMOD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class AddMod : public Opcode {
    QString name() override { return "ADDMOD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class MulMod : public Opcode {
    QString name() override { return "MULMOD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Exp : public Opcode {
    QString name() override { return "EXP"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class SignExtend : public Opcode {
    QString name() override { return "SIGNEXTEND"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Lt : public Opcode {
    QString name() override { return "LT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Gt : public Opcode {
    QString name() override { return "GT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Slt : public Opcode {
    QString name() override { return "SLT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Sgt : public Opcode {
    QString name() override { return "SGT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Eq : public Opcode {
    QString name() override { return "EQ"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class IsZero : public Opcode {
    QString name() override { return "ISZERO"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class And : public Opcode {
    QString name() override { return "AND"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Or : public Opcode {
    QString name() override { return "OR"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Xor : public Opcode {
    QString name() override { return "XOR"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Not : public Opcode {
    QString name() override { return "NOT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Byte : public Opcode {
    QString name() override { return "BYTE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Shl : public Opcode {
    QString name() override { return "SHL"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Shr : public Opcode {
    QString name() override { return "SHR"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Sar : public Opcode {
    QString name() override { return "SAR"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Keccak256 : public Opcode {
    QString name() override { return "KECCAK256"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Address : public Opcode {
    QString name() override { return "ADDRESS"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Balance : public Opcode {
    QString name() override { return "BALANCE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Origin : public Opcode {
    QString name() override { return "ORIGIN"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Caller : public Opcode {
    QString name() override { return "CALLER"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class CallValue : public Opcode {
    QString name() override { return "CALLVALUE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class CallDataLoad : public Opcode {
    QString name() override { return "CALLDATALOAD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool isCallDataLoad() override { return true; }
};
class CallDataSize : public Opcode {
    QString name() override { return "CALLDATASIZE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool isCallDataSize() override { return true; }
};
class CallDataCopy : public Opcode {
    QString name() override { return "CALLDATACOPY"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool isCallDataCopy() override { return true; }
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};
class CodeSize : public Opcode {
    QString name() override { return "CODESIZE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class CodeCopy : public Opcode {
    QString name() override { return "CODECOPY"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};


class GasPrice : public Opcode {
    QString name() override { return "GASPRICE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class ExtCodeSize : public Opcode {
    QString name() override { return "EXTCODESIZE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class ExtCodeCopy : public Opcode {
    QString name() override { return "EXTCODECOPY"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};
class ReturnDataSize : public Opcode {
    QString name() override { return "RETURNDATASIZE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class ReturnDataCopy : public Opcode {
    QString name() override { return "RETURNDATACOPY"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};
class ExtCodeHash : public Opcode {
    QString name() override { return "EXTCODEHASH"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class BlockHash : public Opcode {
    QString name() override { return "BLOCKHASH"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class CoinBase : public Opcode {
    QString name() override { return "COINBASE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Timestamp : public Opcode {
    QString name() override { return "TIMESTAMP"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Number : public Opcode {
    QString name() override { return "NUMBER"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Difficulty : public Opcode {
    QString name() override { return "DIFFICULTY"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class GasLimit : public Opcode {
    QString name() override { return "GASLIMIT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class ChainId : public Opcode {
    QString name() override { return "CHAINID"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class SelfBalance : public Opcode {
    QString name() override { return "SELFBALANCE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class BaseFee : public Opcode {
    QString name() override { return "BASEFEE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class BlobHash : public Opcode {
    QString name() override { return "BLOBHASH"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class BlobBaseFee : public Opcode {
    QString name() override { return "BLOBBASEFEE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class Pop : public Opcode {
    QString name() override { return "POP"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class MLoad : public Opcode {
    QString name() override { return "MLOAD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class MStore : public Opcode {
    QString name() override { return "MSTORE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};
class MStore8 : public Opcode {
    QString name() override { return "MSTORE8"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};
class SLoad : public Opcode {
    QString name() override { return "SLOAD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool isSLoad() override { return true; }
};
class SStore : public Opcode {
    QString name() override { return "SSTORE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    virtual bool isSStore() override { return true; }
    bool pushesNewValue() override { return false; }
};

class Jump : public Opcode {
    QString name() override { return "JUMP"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class JumpI : public Opcode {
    QString name() override { return "JUMPI"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class Pc : public Opcode {
    QString name() override { return "PC"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};

class MSize : public Opcode {
    QString name() override { return "MSIZE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Gas : public Opcode {
    QString name() override { return "GAS"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class JumpDest : public Opcode {
    QString name() override { return "JUMPDEST"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class TLoad : public Opcode {
    QString name() override { return "TLOAD"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class TStore : public Opcode {
    QString name() override { return "TSTORE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class MCopy : public Opcode {
    QString name() override { return "MCOPY"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool editsMemory() override { return true; }
    std::optional<Model::Range> memorySlotsToBeChanged(const std::vector<QString>& stack) override;
    bool pushesNewValue() override { return false; }
};

class Push0 : public Opcode {
    QString name() override { return "PUSH0"; }
    QString description() override;
    bool isPush() override { return true; }
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
};
class Push : public Opcode {
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override { return { { "value", arg } }; }
    QString description() override {
        return "pushes a value to the stack";
    }
    bool isPush() override { return true; }
};

class Push1 : public Push {
    QString name() override { return "PUSH1"; }
    uint32_t pushSize() override { return 1; }
};
class Push2 : public Push {
    QString name() override { return "PUSH2"; }
    uint32_t pushSize() override { return 2; }
};
class Push3 : public Push {
    QString name() override { return "PUSH3"; }
    uint32_t pushSize() override { return 3; }
};
class Push4 : public Push {
    QString name() override { return "PUSH4"; }
    uint32_t pushSize() override { return 4; }
};
class Push5 : public Push {
    QString name() override { return "PUSH5"; }
    uint32_t pushSize() override { return 5; }
};
class Push6 : public Push {
    QString name() override { return "PUSH6"; }
    uint32_t pushSize() override { return 6; }
};
class Push7 : public Push {
    QString name() override { return "PUSH7"; }
    uint32_t pushSize() override { return 7; }
};
class Push8 : public Push {
    QString name() override { return "PUSH8"; }
    uint32_t pushSize() override { return 8; }
};
class Push9 : public Push {
    QString name() override { return "PUSH9"; }
    uint32_t pushSize() override { return 9; }
};
class Push10 : public Push {
    QString name() override { return "PUSH10"; }
    uint32_t pushSize() override { return 10; }
};
class Push11 : public Push {
    QString name() override { return "PUSH11"; }
    uint32_t pushSize() override { return 11; }
};
class Push12 : public Push {
    QString name() override { return "PUSH12"; }
    uint32_t pushSize() override { return 12; }
};
class Push13 : public Push {
    QString name() override { return "PUSH13"; }
    uint32_t pushSize() override { return 13; }
};
class Push14 : public Push {
    QString name() override { return "PUSH14"; }
    uint32_t pushSize() override { return 14; }
};
class Push15 : public Push {
    QString name() override { return "PUSH15"; }
    uint32_t pushSize() override { return 15; }
};
class Push16 : public Push {
    QString name() override { return "PUSH16"; }
    uint32_t pushSize() override { return 16; }
};
class Push17 : public Push {
    QString name() override { return "PUSH17"; }
    uint32_t pushSize() override { return 17; }
};
class Push18 : public Push {
    QString name() override { return "PUSH18"; }
    uint32_t pushSize() override { return 18; }
};
class Push19 : public Push {
    QString name() override { return "PUSH19"; }
    uint32_t pushSize() override { return 19; }
};
class Push20 : public Push {
    QString name() override { return "PUSH20"; }
    uint32_t pushSize() override { return 20; }
};
class Push21 : public Push {
    QString name() override { return "PUSH21"; }
    uint32_t pushSize() override { return 21; }
};
class Push22 : public Push {
    QString name() override { return "PUSH22"; }
    uint32_t pushSize() override { return 22; }
};
class Push23 : public Push {
    QString name() override { return "PUSH23"; }
    uint32_t pushSize() override { return 23; }
};
class Push24 : public Push {
    QString name() override { return "PUSH24"; }
    uint32_t pushSize() override { return 24; }
};
class Push25 : public Push {
    QString name() override { return "PUSH25"; }
    uint32_t pushSize() override { return 25; }
};
class Push26 : public Push {
    QString name() override { return "PUSH26"; }
    uint32_t pushSize() override { return 26; }
};
class Push27 : public Push {
    QString name() override { return "PUSH27"; }
    uint32_t pushSize() override { return 27; }
};
class Push28 : public Push {
    QString name() override { return "PUSH28"; }
    uint32_t pushSize() override { return 28; }
};
class Push29 : public Push {
    QString name() override { return "PUSH29"; }
    uint32_t pushSize() override { return 29; }
};
class Push30 : public Push {
    QString name() override { return "PUSH30"; }
    uint32_t pushSize() override { return 30; }
};
class Push31 : public Push {
    QString name() override { return "PUSH31"; }
    uint32_t pushSize() override { return 31; }
};
class Push32 : public Push {
    QString name() override { return "PUSH32"; }
    uint32_t pushSize() override { return 32; }
};

class Dup : public Opcode {
public:
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override {
        uint32_t dupN = dupSize();
        if (stack.size() < dupN) return { { "value", "ERROR" } };
        return { { "value", stack[stack.size() - dupN] } };
    }
    QString description() override {
        uint32_t dupN = dupSize();
        if (dupN == 1) return "clones the last value on the stack";
        else if (dupN == 2) return "clones the 2nd last value on the stack";
        else if (dupN == 3) return "clones the 3rd last value on the stack";
        return "clones the " + QString::number(dupN) + "th last value on the stack";
    }
    bool pushesNewValue() override { return false; }
};
class Dup1 : public Dup {
    QString name() override { return "DUP1"; }
    uint32_t dupSize() override { return 1; }
};
class Dup2 : public Dup {
    QString name() override { return "DUP2"; }
    uint32_t dupSize() override { return 2; }
};
class Dup3 : public Dup {
    QString name() override { return "DUP3"; }
    uint32_t dupSize() override { return 3; }
};
class Dup4 : public Dup {
    QString name() override { return "DUP4"; }
    uint32_t dupSize() override { return 4; }
};
class Dup5 : public Dup {
    QString name() override { return "DUP5"; }
    uint32_t dupSize() override { return 5; }
};
class Dup6 : public Dup {
    QString name() override { return "DUP6"; }
    uint32_t dupSize() override { return 6; }
};
class Dup7 : public Dup {
    QString name() override { return "DUP7"; }
    uint32_t dupSize() override { return 7; }
};
class Dup8 : public Dup {
    QString name() override { return "DUP8"; }
    uint32_t dupSize() override { return 8; }
};
class Dup9 : public Dup {
    QString name() override { return "DUP9"; }
    uint32_t dupSize() override { return 9; }
};
class Dup10 : public Dup {
    QString name() override { return "DUP10"; }
    uint32_t dupSize() override { return 10; }
};
class Dup11 : public Dup {
    QString name() override { return "DUP11"; }
    uint32_t dupSize() override { return 11; }
};
class Dup12 : public Dup {
    QString name() override { return "DUP12"; }
    uint32_t dupSize() override { return 12; }
};
class Dup13 : public Dup {
    QString name() override { return "DUP13"; }
    uint32_t dupSize() override { return 13; }
};
class Dup14 : public Dup {
    QString name() override { return "DUP14"; }
    uint32_t dupSize() override { return 14; }
};
class Dup15 : public Dup {
    QString name() override { return "DUP15"; }
    uint32_t dupSize() override { return 15; }
};
class Dup16 : public Dup {
    QString name() override { return "DUP16"; }
    uint32_t dupSize() override { return 16; }
};

class Swap : public Opcode {
public:
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override {
        uint32_t swapN = swapSize();
        if (stack.size() <= swapN) return { { "value", "ERROR" } };
        return { { "value", stack[stack.size() - swapN - 1] } };
    }
    QString description() override {
        uint32_t swapN = swapSize();
        if (swapN == 1) return "swaps the last two values on the stack";
        else if (swapN == 2) return "swaps the top of the stack with the 3rd last element";
        return "swaps the top of the stack with the " + QString::number(swapN+1) + "th last element";
    }
    bool pushesNewValue() override { return false; }
};

class Swap1 : public Swap {
    QString name() override { return "SWAP1"; }
    uint32_t swapSize() override { return 1; }
};
class Swap2 : public Swap {
    QString name() override { return "SWAP2"; }
    uint32_t swapSize() override { return 2; }
};
class Swap3 : public Swap {
    QString name() override { return "SWAP3"; }
    uint32_t swapSize() override { return 3; }
};
class Swap4 : public Swap {
    QString name() override { return "SWAP4"; }
    uint32_t swapSize() override { return 4; }
};
class Swap5 : public Swap {
    QString name() override { return "SWAP5"; }
    uint32_t swapSize() override { return 5; }
};
class Swap6 : public Swap {
    QString name() override { return "SWAP6"; }
    uint32_t swapSize() override { return 6; }
};
class Swap7 : public Swap {
    QString name() override { return "SWAP7"; }
    uint32_t swapSize() override { return 7; }
};
class Swap8 : public Swap {
    QString name() override { return "SWAP8"; }
    uint32_t swapSize() override { return 8; }
};
class Swap9 : public Swap {
    QString name() override { return "SWAP9"; }
    uint32_t swapSize() override { return 9; }
};
class Swap10 : public Swap {
    QString name() override { return "SWAP10"; }
    uint32_t swapSize() override { return 10; }
};
class Swap11 : public Swap {
    QString name() override { return "SWAP11"; }
    uint32_t swapSize() override { return 11; }
};
class Swap12 : public Swap {
    QString name() override { return "SWAP12"; }
    uint32_t swapSize() override { return 12; }
};
class Swap13 : public Swap {
    QString name() override { return "SWAP13"; }
    uint32_t swapSize() override { return 13; }
};
class Swap14 : public Swap {
    QString name() override { return "SWAP14"; }
    uint32_t swapSize() override { return 14; }
};
class Swap15 : public Swap {
    QString name() override { return "SWAP15"; }
    uint32_t swapSize() override { return 15; }
};
class Swap16 : public Swap {
    QString name() override { return "SWAP16"; }
    uint32_t swapSize() override { return 16; }
};

class Log0 : public Opcode {
    QString name() override { return "LOG0"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class Log1 : public Opcode {
    QString name() override { return "LOG1"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class Log2 : public Opcode {
    QString name() override { return "LOG2"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class Log3 : public Opcode {
    QString name() override { return "LOG3"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};
class Log4 : public Opcode {
    QString name() override { return "LOG4"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool pushesNewValue() override { return false; }
};

class Create : public Opcode {
    QString name() override { return "CREATE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    QString callsContract(const std::vector<QString>& stack, QString arg = {}) override;
    Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) override;
    bool pushesNewValue() override { return false; }
};
class Call : public Opcode {
    QString name() override { return "CALL"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    QString callsContract(const std::vector<QString>& stack, QString arg = {}) override;
    Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) override;
    bool pushesNewValue() override { return false; }
};
class CallCode : public Opcode {
    QString name() override { return "CALLCODE"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    QString callsContract(const std::vector<QString>& stack, QString arg = {}) override;
    Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) override;
    bool pushesNewValue() override { return false; }
};
class Return : public Opcode {
    QString name() override { return "RETURN"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool decreasesDepth() override { return true; }
    bool pushesNewValue() override { return false; }
};
class DelegateCall : public Opcode {
    QString name() override { return "DELEGATECALL"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    QString callsContract(const std::vector<QString>& stack, QString arg = {}) override;
    Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) override;
    bool pushesNewValue() override { return false; }
};
class Create2 : public Opcode {
    QString name() override { return "CREATE2"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    QString callsContract(const std::vector<QString>& stack, QString arg = {}) override;
    Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) override;
    bool pushesNewValue() override { return false; }
};

class StaticCall : public Opcode {
    QString name() override { return "STATICCALL"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    QString callsContract(const std::vector<QString>& stack, QString arg = {}) override;
    Model::Calldata calldata(const std::vector<QString>& stack, const std::vector<QString>& memory) override;
    bool pushesNewValue() override { return false; }
};
class Revert : public Opcode {
    QString name() override { return "REVERT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool decreasesDepth() override { return true; }
    bool pushesNewValue() override { return false; }
};
class SelfDestruct : public Opcode {
    QString name() override { return "SELFDESTRUCT"; }
    QString description() override;
    std::vector<std::pair<QString,QString>> functionArgs(const std::vector<QString>& stack, const QString& arg = {}) override;
    bool decreasesDepth() override { return true; }
    bool pushesNewValue() override { return false; }
};

#endif // OPCODE_H
