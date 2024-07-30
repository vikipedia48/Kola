#include "opcode.h"


std::unique_ptr<Opcode> Opcode::fromName(const QString &name)
{
    if (name == "STOP") return std::unique_ptr<Opcode>(new Stop());
    if (name == "ADD") return std::unique_ptr<Opcode>(new Add());
    if (name == "MUL") return std::unique_ptr<Opcode>(new Mul());
    if (name == "SUB") return std::unique_ptr<Opcode>(new Sub());
    if (name == "DIV") return std::unique_ptr<Opcode>(new Div());
    if (name == "SDIV") return std::unique_ptr<Opcode>(new SDiv());
    if (name == "MOD") return std::unique_ptr<Opcode>(new Mod());
    if (name == "SMOD") return std::unique_ptr<Opcode>(new SMod());
    if (name == "ADDMOD") return std::unique_ptr<Opcode>(new AddMod());
    if (name == "MULMOD") return std::unique_ptr<Opcode>(new MulMod());
    if (name == "EXP") return std::unique_ptr<Opcode>(new Exp());
    if (name == "SIGNEXTEND") return std::unique_ptr<Opcode>(new SignExtend());

    if (name == "LT") return std::unique_ptr<Opcode>(new Lt());
    if (name == "GT") return std::unique_ptr<Opcode>(new Gt());
    if (name == "SLT") return std::unique_ptr<Opcode>(new Slt());
    if (name == "SGT") return std::unique_ptr<Opcode>(new Sgt());
    if (name == "EQ") return std::unique_ptr<Opcode>(new Eq());
    if (name == "ISZERO") return std::unique_ptr<Opcode>(new IsZero());
    if (name == "AND") return std::unique_ptr<Opcode>(new And());
    if (name == "OR") return std::unique_ptr<Opcode>(new Or());
    if (name == "XOR") return std::unique_ptr<Opcode>(new Xor());
    if (name == "NOT") return std::unique_ptr<Opcode>(new Not());
    if (name == "BYTE") return std::unique_ptr<Opcode>(new Byte());
    if (name == "SHL") return std::unique_ptr<Opcode>(new Shl());
    if (name == "SHR") return std::unique_ptr<Opcode>(new Shr());
    if (name == "SAR") return std::unique_ptr<Opcode>(new Sar());
    if (name == "KECCAK256" || name == "SHA3") return std::unique_ptr<Opcode>(new Keccak256());

    if (name == "ADDRESS") return std::unique_ptr<Opcode>(new Address());
    if (name == "BALANCE") return std::unique_ptr<Opcode>(new Balance());
    if (name == "ORIGIN") return std::unique_ptr<Opcode>(new Origin());
    if (name == "CALLER") return std::unique_ptr<Opcode>(new Caller());
    if (name == "CALLVALUE") return std::unique_ptr<Opcode>(new CallValue());
    if (name == "CALLDATALOAD") return std::unique_ptr<Opcode>(new CallDataLoad());
    if (name == "CALLDATASIZE") return std::unique_ptr<Opcode>(new CallDataSize());
    if (name == "CALLDATACOPY") return std::unique_ptr<Opcode>(new CallDataCopy());
    if (name == "CODESIZE") return std::unique_ptr<Opcode>(new CodeSize());
    if (name == "CODECOPY") return std::unique_ptr<Opcode>(new CodeCopy());
    if (name == "GASPRICE") return std::unique_ptr<Opcode>(new GasPrice());
    if (name == "EXTCODESIZE") return std::unique_ptr<Opcode>(new ExtCodeSize());
    if (name == "EXTCODECOPY") return std::unique_ptr<Opcode>(new ExtCodeCopy());
    if (name == "RETURNDATASIZE") return std::unique_ptr<Opcode>(new ReturnDataSize());
    if (name == "RETURNDATACOPY") return std::unique_ptr<Opcode>(new ReturnDataCopy());
    if (name == "EXTCODEHASH") return std::unique_ptr<Opcode>(new ExtCodeHash());
    if (name == "BLOCKHASH") return std::unique_ptr<Opcode>(new BlockHash());
    if (name == "COINBASE") return std::unique_ptr<Opcode>(new CoinBase());
    if (name == "TIMESTAMP") return std::unique_ptr<Opcode>(new Timestamp());
    if (name == "NUMBER") return std::unique_ptr<Opcode>(new Number());
    if (name == "DIFFICULTY") return std::unique_ptr<Opcode>(new Difficulty());
    if (name == "GASLIMIT") return std::unique_ptr<Opcode>(new GasLimit());
    if (name == "CHAINID") return std::unique_ptr<Opcode>(new ChainId());
    if (name == "SELFBALANCE") return std::unique_ptr<Opcode>(new SelfBalance());
    if (name == "BASEFEE") return std::unique_ptr<Opcode>(new BaseFee());
    if (name == "BLOBHASH") return std::unique_ptr<Opcode>(new BlobHash());
    if (name == "BLOBBASEFEE") return std::unique_ptr<Opcode>(new BlobBaseFee());

    if (name == "POP") return std::unique_ptr<Opcode>(new Pop());
    if (name == "MLOAD") return std::unique_ptr<Opcode>(new MLoad());
    if (name == "MSTORE") return std::unique_ptr<Opcode>(new MStore());
    if (name == "MSTORE8") return std::unique_ptr<Opcode>(new MStore8());
    if (name == "SLOAD") return std::unique_ptr<Opcode>(new SLoad());
    if (name == "SSTORE") return std::unique_ptr<Opcode>(new SStore());
    if (name == "JUMP") return std::unique_ptr<Opcode>(new Jump());
    if (name == "JUMPI") return std::unique_ptr<Opcode>(new JumpI());
    if (name == "PC") return std::unique_ptr<Opcode>(new Pc());
    if (name == "MSIZE") return std::unique_ptr<Opcode>(new MSize());
    if (name == "GAS") return std::unique_ptr<Opcode>(new Gas());
    if (name == "JUMPDEST") return std::unique_ptr<Opcode>(new JumpDest());
    if (name == "TLOAD") return std::unique_ptr<Opcode>(new TLoad());
    if (name == "TSTORE") return std::unique_ptr<Opcode>(new TStore());
    if (name == "MCOPY") return std::unique_ptr<Opcode>(new MCopy());

    if (name == "PUSH0") return std::unique_ptr<Opcode>(new Push0());
    if (name == "PUSH1") return std::unique_ptr<Opcode>(new Push1());
    if (name == "PUSH2") return std::unique_ptr<Opcode>(new Push2());
    if (name == "PUSH3") return std::unique_ptr<Opcode>(new Push3());
    if (name == "PUSH4") return std::unique_ptr<Opcode>(new Push4());
    if (name == "PUSH5") return std::unique_ptr<Opcode>(new Push5());
    if (name == "PUSH6") return std::unique_ptr<Opcode>(new Push6());
    if (name == "PUSH7") return std::unique_ptr<Opcode>(new Push7());
    if (name == "PUSH8") return std::unique_ptr<Opcode>(new Push8());
    if (name == "PUSH9") return std::unique_ptr<Opcode>(new Push9());
    if (name == "PUSH10") return std::unique_ptr<Opcode>(new Push10());
    if (name == "PUSH11") return std::unique_ptr<Opcode>(new Push11());
    if (name == "PUSH12") return std::unique_ptr<Opcode>(new Push12());
    if (name == "PUSH13") return std::unique_ptr<Opcode>(new Push13());
    if (name == "PUSH14") return std::unique_ptr<Opcode>(new Push14());
    if (name == "PUSH15") return std::unique_ptr<Opcode>(new Push15());
    if (name == "PUSH16") return std::unique_ptr<Opcode>(new Push16());
    if (name == "PUSH17") return std::unique_ptr<Opcode>(new Push17());
    if (name == "PUSH18") return std::unique_ptr<Opcode>(new Push18());
    if (name == "PUSH19") return std::unique_ptr<Opcode>(new Push19());
    if (name == "PUSH20") return std::unique_ptr<Opcode>(new Push20());
    if (name == "PUSH21") return std::unique_ptr<Opcode>(new Push21());
    if (name == "PUSH22") return std::unique_ptr<Opcode>(new Push22());
    if (name == "PUSH23") return std::unique_ptr<Opcode>(new Push23());
    if (name == "PUSH24") return std::unique_ptr<Opcode>(new Push24());
    if (name == "PUSH25") return std::unique_ptr<Opcode>(new Push25());
    if (name == "PUSH26") return std::unique_ptr<Opcode>(new Push26());
    if (name == "PUSH27") return std::unique_ptr<Opcode>(new Push27());
    if (name == "PUSH28") return std::unique_ptr<Opcode>(new Push28());
    if (name == "PUSH29") return std::unique_ptr<Opcode>(new Push29());
    if (name == "PUSH30") return std::unique_ptr<Opcode>(new Push30());
    if (name == "PUSH31") return std::unique_ptr<Opcode>(new Push31());
    if (name == "PUSH32") return std::unique_ptr<Opcode>(new Push32());

    if (name == "DUP1") return std::unique_ptr<Opcode>(new Dup1());
    if (name == "DUP2") return std::unique_ptr<Opcode>(new Dup2());
    if (name == "DUP3") return std::unique_ptr<Opcode>(new Dup3());
    if (name == "DUP4") return std::unique_ptr<Opcode>(new Dup4());
    if (name == "DUP5") return std::unique_ptr<Opcode>(new Dup5());
    if (name == "DUP6") return std::unique_ptr<Opcode>(new Dup6());
    if (name == "DUP7") return std::unique_ptr<Opcode>(new Dup7());
    if (name == "DUP8") return std::unique_ptr<Opcode>(new Dup8());
    if (name == "DUP9") return std::unique_ptr<Opcode>(new Dup9());
    if (name == "DUP10") return std::unique_ptr<Opcode>(new Dup10());
    if (name == "DUP11") return std::unique_ptr<Opcode>(new Dup11());
    if (name == "DUP12") return std::unique_ptr<Opcode>(new Dup12());
    if (name == "DUP13") return std::unique_ptr<Opcode>(new Dup13());
    if (name == "DUP14") return std::unique_ptr<Opcode>(new Dup14());
    if (name == "DUP15") return std::unique_ptr<Opcode>(new Dup15());
    if (name == "DUP16") return std::unique_ptr<Opcode>(new Dup16());

    if (name == "SWAP1") return std::unique_ptr<Opcode>(new Swap1());
    if (name == "SWAP2") return std::unique_ptr<Opcode>(new Swap2());
    if (name == "SWAP3") return std::unique_ptr<Opcode>(new Swap3());
    if (name == "SWAP4") return std::unique_ptr<Opcode>(new Swap4());
    if (name == "SWAP5") return std::unique_ptr<Opcode>(new Swap5());
    if (name == "SWAP6") return std::unique_ptr<Opcode>(new Swap6());
    if (name == "SWAP7") return std::unique_ptr<Opcode>(new Swap7());
    if (name == "SWAP8") return std::unique_ptr<Opcode>(new Swap8());
    if (name == "SWAP9") return std::unique_ptr<Opcode>(new Swap9());
    if (name == "SWAP10") return std::unique_ptr<Opcode>(new Swap10());
    if (name == "SWAP11") return std::unique_ptr<Opcode>(new Swap11());
    if (name == "SWAP12") return std::unique_ptr<Opcode>(new Swap12());
    if (name == "SWAP13") return std::unique_ptr<Opcode>(new Swap13());
    if (name == "SWAP14") return std::unique_ptr<Opcode>(new Swap14());
    if (name == "SWAP15") return std::unique_ptr<Opcode>(new Swap15());
    if (name == "SWAP16") return std::unique_ptr<Opcode>(new Swap16());

    if (name == "LOG0") return std::unique_ptr<Opcode>(new Log0());
    if (name == "LOG1") return std::unique_ptr<Opcode>(new Log1());
    if (name == "LOG2") return std::unique_ptr<Opcode>(new Log2());
    if (name == "LOG3") return std::unique_ptr<Opcode>(new Log3());
    if (name == "LOG4") return std::unique_ptr<Opcode>(new Log4());

    if (name == "CREATE") return std::unique_ptr<Opcode>(new Create());
    if (name == "CALL") return std::unique_ptr<Opcode>(new Call());
    if (name == "CALLCODE") return std::unique_ptr<Opcode>(new CallCode());
    if (name == "RETURN") return std::unique_ptr<Opcode>(new Return());
    if (name == "DELEGATECALL") return std::unique_ptr<Opcode>(new DelegateCall());
    if (name == "CREATE2") return std::unique_ptr<Opcode>(new Create2());
    if (name == "STATICCALL") return std::unique_ptr<Opcode>(new StaticCall());
    if (name == "REVERT") return std::unique_ptr<Opcode>(new Revert());
    if (name == "SELFDESTRUCT") return std::unique_ptr<Opcode>(new SelfDestruct());
    if (name == "INVALID") return std::unique_ptr<Opcode>(new Invalid());

    return std::unique_ptr<Opcode>(new Unknown());
}
std::vector<std::pair<QString, QString> > Invalid::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Invalid::description()
{
    return "unrecognized opcode";
}

std::vector<std::pair<QString, QString> > Stop::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Stop::description()
{
    return "halts execution of the contract";
}

std::vector<std::pair<QString, QString> > Add::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Add::description()
{
    return "a + b";
}

QString Mul::description()
{
    return "a * b";
}

std::vector<std::pair<QString, QString> > Mul::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Sub::description()
{
    return "a - b";
}

std::vector<std::pair<QString, QString> > Sub::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Div::description()
{
    return "a // b";
}

std::vector<std::pair<QString, QString> > Div::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString SDiv::description()
{
    return "a // b";
}

std::vector<std::pair<QString, QString> > SDiv::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Mod::description()
{
    return "a % b";
}

std::vector<std::pair<QString, QString> > Mod::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString SMod::description()
{
    return "a % b";
}

std::vector<std::pair<QString, QString> > SMod::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString AddMod::description()
{
    return "(a + b) % N";
}

std::vector<std::pair<QString, QString> > AddMod::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) }, { "N", *(++iter) } };
}

QString MulMod::description()
{
    return "(a * b) % N";
}

std::vector<std::pair<QString, QString> > MulMod::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) }, { "N", *(++iter) } };
}

QString Exp::description()
{
    return "a ** b";
}

std::vector<std::pair<QString, QString> > Exp::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString SignExtend::description()
{
    return "SIGNEXTEND(x, b)";
}

std::vector<std::pair<QString, QString> > SignExtend::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "b", *iter }, { "x", *(++iter) } };
}

QString Lt::description()
{
    return "a < b";
}

std::vector<std::pair<QString, QString> > Lt::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Gt::description()
{
    return "a > b";
}

std::vector<std::pair<QString, QString> > Gt::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Slt::description()
{
    return "a < b";
}

std::vector<std::pair<QString, QString> > Slt::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Sgt::description()
{
    return "a > b";
}

std::vector<std::pair<QString, QString> > Sgt::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Eq::description()
{
    return "a == b";
}

std::vector<std::pair<QString, QString> > Eq::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString IsZero::description()
{
    return "a == 0";
}

std::vector<std::pair<QString, QString> > IsZero::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter } };
}

QString And::description()
{
    return "a % b";
}

std::vector<std::pair<QString, QString> > And::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Or::description()
{
    return "a | b";
}

std::vector<std::pair<QString, QString> > Or::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Xor::description()
{
    return "a ^ b";
}

std::vector<std::pair<QString, QString> > Xor::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter }, { "b", *(++iter) } };
}

QString Not::description()
{
    return "~a";
}

std::vector<std::pair<QString, QString> > Not::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "a", *iter } };
}

QString Byte::description()
{
    return "ith byte of x";
}

std::vector<std::pair<QString, QString> > Byte::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "i", *iter }, { "x", *(++iter) } };
}

QString Shl::description()
{
    return "value << shift";
}

std::vector<std::pair<QString, QString> > Shl::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "shift", *iter }, { "value", *(++iter) } };
}

QString Shr::description()
{
    return "value >> shift";
}

std::vector<std::pair<QString, QString> > Shr::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "shift", *iter }, { "value", *(++iter) } };
}

QString Sar::description()
{
    return "value >> shift";
}

std::vector<std::pair<QString, QString> > Sar::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "shift", *iter }, { "value", *(++iter) } };
}

QString Keccak256::description()
{
    return "keccak256(memory[offset:offset+length])";
}

std::vector<std::pair<QString, QString> > Keccak256::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "length", *(++iter) } };
}

QString Address::description()
{
    return "address of the executing contract";
}

std::vector<std::pair<QString, QString> > Address::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Balance::description()
{
    return "address balance in wei";
}

std::vector<std::pair<QString, QString> > Balance::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "addr", *iter } };
}

QString Origin::description()
{
    return "transaction origin address";
}

std::vector<std::pair<QString, QString> > Origin::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Caller::description()
{
    return "message caller address";
}

std::vector<std::pair<QString, QString> > Caller::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString CallValue::description()
{
    return "message funds in wei";
}

std::vector<std::pair<QString, QString> > CallValue::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString CallDataLoad::description()
{
    return "msg.data[i:i+32]";
}

std::vector<std::pair<QString, QString> > CallDataLoad::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "i", *iter } };
}

QString CallDataSize::description()
{
    return "message data length in bytes";
}

std::vector<std::pair<QString, QString> > CallDataSize::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString CallDataCopy::description()
{
    return "memory[destOffset:destOffset+length] = msg.data[offset:offset+length]";
}

std::vector<std::pair<QString, QString> > CallDataCopy::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "destOffset", *iter }, { "offset", *(++iter) }, { "length", *(++iter) } };
}

std::optional<Model::Range > CallDataCopy::memorySlotsToBeChanged(const std::vector<QString> &stack)
{

    if(stack.size() < 3) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    iter += 2;
    auto _length = *iter;
    uint32_t length = _length.toUInt(&ok, 16);
    if (!ok) return std::nullopt;
    if (length == 0) return std::nullopt;

    uint32_t firstSlot = start / 32;
    uint32_t lastSlot = (start + length - 1) / 32;
    return Model::Range(firstSlot, lastSlot - firstSlot);
}

QString CodeSize::description()
{
    return "length of the executing contract's code in bytes";
}

std::vector<std::pair<QString, QString> > CodeSize::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString CodeCopy::description()
{
    return "memory[destOffset:destOffset+length] = address(this).code[offset:offset+length]";
}

std::vector<std::pair<QString, QString> > CodeCopy::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "destOffset", *iter }, { "offset", *(++iter) }, { "length", *(++iter) } };
}

std::optional<Model::Range > CodeCopy::memorySlotsToBeChanged(const std::vector<QString> &stack)
{
    if(stack.size() < 3) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    iter += 2;
    auto _length = *iter;
    uint32_t length = _length.toUInt(&ok, 16);
    if (!ok) return std::nullopt;
    if (length == 0) return std::nullopt;

    uint32_t firstSlot = start / 32;
    uint32_t lastSlot = (start + length - 1) / 32;
    return Model::Range (firstSlot, lastSlot - firstSlot);
}

QString GasPrice::description()
{
    return "gas price of the executing transaction, in wei per unit of gas";
}

std::vector<std::pair<QString, QString> > GasPrice::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString ExtCodeSize::description()
{
    return "length of the contract bytecode at addr, in bytes";
}

std::vector<std::pair<QString, QString> > ExtCodeSize::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "addr", *iter } };
}

QString ExtCodeCopy::description()
{
    return "memory[destOffset:destOffset+length] = address(addr).code[offset:offset+length]";
}

std::vector<std::pair<QString, QString> > ExtCodeCopy::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 4) return {};
    auto iter = stack.rbegin();
    return { { "addr", *iter }, { "destOffset", *(++iter) }, { "offset", *(++iter) }, { "length", *(++iter) } };
}

std::optional<Model::Range > ExtCodeCopy::memorySlotsToBeChanged(const std::vector<QString> &stack)
{
    if(stack.size() < 4) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    ++iter;
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    iter += 2;
    auto _length = *iter;
    uint32_t length = _length.toUInt(&ok, 16);
    if (!ok) return std::nullopt;
    if (length == 0) return std::nullopt;

    uint32_t firstSlot = start / 32;
    uint32_t lastSlot = (start + length - 1) / 32;
    return Model::Range(firstSlot, lastSlot - firstSlot);
}

QString ReturnDataSize::description()
{
    return "the size of the returned data from the last external call, in bytes";
}

std::vector<std::pair<QString, QString> > ReturnDataSize::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString ReturnDataCopy::description()
{
    return "memory[destOffset:destOffset+length] = RETURNDATA[offset:offset+length]";
}

std::vector<std::pair<QString, QString> > ReturnDataCopy::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "destOffset", *iter }, { "offset", *(++iter) }, { "length", *(++iter) } };
}

std::optional<Model::Range > ReturnDataCopy::memorySlotsToBeChanged(const std::vector<QString> &stack)
{
    if(stack.size() < 3) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    iter += 2;
    auto _length = *iter;
    uint32_t length = _length.toUInt(&ok, 16);
    if (!ok) return std::nullopt;
    if (length == 0) return std::nullopt;

    uint32_t firstSlot = start / 32;
    uint32_t lastSlot = (start + length - 1) / 32;
    return Model::Range(firstSlot, lastSlot - firstSlot);
}

QString ExtCodeHash::description()
{
    return "hash of the contract bytecode at addr (or 0 if it doesn't exist)";
}

std::vector<std::pair<QString, QString> > ExtCodeHash::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "addr", *iter } };
}

QString BlockHash::description()
{
    return "hash of the specific block, only valid for the 256 most recent blocks, excluding the current one";
}

std::vector<std::pair<QString, QString> > BlockHash::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "blockNumber", *iter } };
}

QString CoinBase::description()
{
    return "address of the current block's miner";
}

std::vector<std::pair<QString, QString> > CoinBase::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Timestamp::description()
{
    return "current block's Unix timestamp in seconds";
}

std::vector<std::pair<QString, QString> > Timestamp::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Number::description()
{
    return "current block's number";
}

std::vector<std::pair<QString, QString> > Number::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Difficulty::description()
{
    return "current block's difficulty";
}

std::vector<std::pair<QString, QString> > Difficulty::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString GasLimit::description()
{
    return "current block's gas limit";
}

std::vector<std::pair<QString, QString> > GasLimit::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString ChainId::description()
{
    return "current network's chain id";
}

std::vector<std::pair<QString, QString> > ChainId::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString SelfBalance::description()
{
    return "balance of the executing contract in wei";
}

std::vector<std::pair<QString, QString> > SelfBalance::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString BaseFee::description()
{
    return "current block's base fee";
}

std::vector<std::pair<QString, QString> > BaseFee::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString BlobHash::description()
{
    return "the executing transaction's index'th blob versioned hash";
}

std::vector<std::pair<QString, QString> > BlobHash::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "index", *iter } };
}

QString BlobBaseFee::description()
{
    return "current block's blob base fee";
}

std::vector<std::pair<QString, QString> > BlobBaseFee::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Pop::description()
{
    return "POP()";
}

std::vector<std::pair<QString, QString> > Pop::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "_", *iter } };
}

QString MLoad::description()
{
    return "memory[offset:offset+32]";
}

std::vector<std::pair<QString, QString> > MLoad::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter } };
}

QString MStore::description()
{
    return "memory[offset:offset+32] = value";
}

std::vector<std::pair<QString, QString> > MStore::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "value", *(++iter) } };
}

std::optional<Model::Range > MStore::memorySlotsToBeChanged(const std::vector<QString> &stack)
{
    if(stack.size() < 2) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    uint32_t firstSlot = start / 32;
    uint32_t lastSlot = (start + 31) / 32;
    return Model::Range(firstSlot, lastSlot - firstSlot);
}

QString MStore8::description()
{
    return "memory[offset] = value & 0xFF";
}

std::vector<std::pair<QString, QString> > MStore8::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "value", *(++iter) } };
}

std::optional<Model::Range > MStore8::memorySlotsToBeChanged(const std::vector<QString> &stack)
{
    if(stack.size() < 2) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    uint32_t firstSlot = start / 32;
    return Model::Range(firstSlot, 0);
}

QString SLoad::description()
{
    return "storage[key]";
}

std::vector<std::pair<QString, QString> > SLoad::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "key", *iter } };
}

QString SStore::description()
{
    return "storage[key] = value";
}

std::vector<std::pair<QString, QString> > SStore::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "key", *iter }, { "value", *(++iter) } };
}

QString Jump::description()
{
    return "$pc = destination";
}

std::vector<std::pair<QString, QString> > Jump::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "destination", *iter } };
}

QString JumpI::description()
{
    return "$pc = destination, if condition isn't zero";
}

std::vector<std::pair<QString, QString> > JumpI::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "destination", *iter }, { "condition", *(++iter) } };
}

QString Pc::description()
{
    return "program counter";
}

std::vector<std::pair<QString, QString> > Pc::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString MSize::description()
{
    return "size of memory for this contract execution, in bytes";
}

std::vector<std::pair<QString, QString> > MSize::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Gas::description()
{
    return "remaining gas";
}

std::vector<std::pair<QString, QString> > Gas::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString JumpDest::description()
{
    return "metadata to annotate possible jump destinations";
}

std::vector<std::pair<QString, QString> > JumpDest::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString TLoad::description()
{
    return "transient[key]";
}

std::vector<std::pair<QString, QString> > TLoad::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "key", *iter } };
}

QString TStore::description()
{
    return "transient[key] = value";
}

std::vector<std::pair<QString, QString> > TStore::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "key", *iter }, { "value", *(++iter) } };
}

QString MCopy::description()
{
    return "memory[destOffset:destOffset+length] = memory[offset:offset+length]";
}

std::vector<std::pair<QString, QString> > MCopy::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "destOffset", *iter }, { "offset", *(++iter) }, { "length", *(++iter) } };
}

std::optional<Model::Range > MCopy::memorySlotsToBeChanged(const std::vector<QString> &stack)
{
    if(stack.size() < 2) return std::nullopt;
    bool ok;

    auto iter = stack.rbegin();
    auto _start = *iter;
    uint32_t start = _start.toUInt(&ok, 16);
    if (!ok) return std::nullopt;

    iter += 2;
    auto _length = *iter;
    uint32_t length = _length.toUInt(&ok, 16);
    if (!ok) return std::nullopt;
    if (length == 0) return std::nullopt;

    uint32_t firstSlot = start / 32;
    uint32_t lastSlot = (start + length - 1) / 32;
    return Model::Range(firstSlot, lastSlot - firstSlot);
}

QString Push0::description()
{
    return "pushes 0 onto the stack";
}

std::vector<std::pair<QString, QString> > Push0::functionArgs(const std::vector<QString> &stack, const QString& arg)
{
    return {};
}

QString Log0::description()
{
    return "fires an event(memory[offset:offset+length])";
}

std::vector<std::pair<QString, QString> > Log0::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "length", *(++iter) } };
}

QString Log1::description()
{
    return "fires an event(memory[offset:offset+length], topic0)";
}

std::vector<std::pair<QString, QString> > Log1::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "length", *(++iter) }, { "topic0", *(++iter) } };
}

QString Log2::description()
{
    return "fires an event(memory[offset:offset+length], topic0, topic1)";
}

std::vector<std::pair<QString, QString> > Log2::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 4) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "value", *(++iter) }, { "topic0", *(++iter) }, { "topic1", *(++iter) } };
}

QString Log3::description()
{
    return "fires an event(memory[offset:offset+length], topic0, topic1, topic2)";
}

std::vector<std::pair<QString, QString> > Log3::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 5) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "value", *(++iter) }, { "topic0", *(++iter) }, { "topic1", *(++iter) }, { "topic2", *(++iter) } };
}

QString Log4::description()
{
    return "fires an event(memory[offset:offset+length], topic0, topic1, topic2, topic3)";
}

std::vector<std::pair<QString, QString> > Log4::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 6) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "value", *(++iter) }, { "topic0", *(++iter) }, { "topic1", *(++iter) }, { "topic2", *(++iter) }, { "topic3", *(++iter) } };
}

QString Create::description()
{
    return "creates a child contract and returns its address; addr = new memory[offset:offset+length].value(value)";
}

std::vector<std::pair<QString, QString> > Create::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 3) return {};
    auto iter = stack.rbegin();
    return { { "value", *iter }, { "offset", *(++iter) }, { "length", *(++iter) } };
}

QString Create::callsContract(const std::vector<QString> &stack, QString arg)
{
    return "new contract (" + arg + ")";
}

Model::Calldata _calldata(const std::vector<QString>& stack, const std::vector<QString> &memory, uint offset, uint length) {
    auto absoluteLastMemoryIndex = offset+length;
    if (absoluteLastMemoryIndex >= memory.size()*32) return {};

    std::vector<std::optional<QChar>> bytes;
    bytes.reserve(length*2);
    for(uint i = offset; i < absoluteLastMemoryIndex; ++i) {
        int vectorIndex = i/32;
        int charIndex = (i - vectorIndex * 32) % 32;
        bytes.push_back(memory[vectorIndex].at(charIndex));
        bytes.push_back(memory[vectorIndex].at(charIndex+1));
    }

    return Model::Calldata(std::move(bytes), length);
}

Model::Calldata Create::calldata(const std::vector<QString>& stack, const std::vector<QString> &memory)
{
    if (stack.size() < 3) return {};
    auto iter = stack.rbegin();
    auto _offset = *(iter+1);
    auto _length = *(iter+2);
    bool ok1, ok2;
    auto offset = _offset.toUInt(&ok1, 16);
    auto length = _length.toUInt(&ok2, 16);
    if (!ok1 || !ok2) return {};
    return _calldata(stack, memory, offset, length);
}

QString Call::description()
{
    return "calls a method in another contract and returns success; memory[retOffset:retOffset+retLength] = address(addr).call.gas(gas).value(value) (memory[argsOffset:argsOffset+argsLength])";
}

std::vector<std::pair<QString, QString> > Call::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 7) return {};
    auto iter = stack.rbegin();
    return { { "gas", *iter }, { "addr", *(++iter) }, { "value", *(++iter) }, { "argsOffset", *(++iter) }, { "argsLength", *(++iter) }, { "retOffset", *(++iter) }, { "retLength", *(++iter) } };
}

QString Call::callsContract(const std::vector<QString> &stack, QString arg)
{
    if(stack.size() < 1) return "0x";
    auto iter = stack.rbegin();
    return "0x" + *(++iter);
}

Model::Calldata Call::calldata(const std::vector<QString> &stack, const std::vector<QString> &memory)
{
    if (stack.size() < 7) return {};
    auto iter = stack.rbegin();
    auto _offset = *(iter+3);
    auto _length = *(iter+4);
    bool ok1, ok2;
    auto offset = _offset.toUInt(&ok1, 16);
    auto length = _length.toUInt(&ok2, 16);
    if (!ok1 || !ok2) return {};
    return _calldata(stack, memory, offset, length);
}

QString CallCode::description()
{
    return "obsolete DELEGATECALL";
}

std::vector<std::pair<QString, QString> > CallCode::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 7) return {};
    auto iter = stack.rbegin();
    return { { "gas", *iter }, { "addr", *(++iter) }, { "value", *(++iter) }, { "argsOffset", *(++iter) }, { "argsLength", *(++iter) }, { "retOffset", *(++iter) }, { "retLength", *(++iter) } };
}

QString CallCode::callsContract(const std::vector<QString> &stack, QString arg)
{
    if(stack.size() < 1) return "0x";
    auto iter = stack.rbegin();
    return "0x" + *(++iter);
}

Model::Calldata CallCode::calldata(const std::vector<QString> &stack, const std::vector<QString> &memory)
{
    if (stack.size() < 7) return {};
    auto iter = stack.rbegin();
    auto _offset = *(iter+3);
    auto _length = *(iter+4);
    bool ok1, ok2;
    auto offset = _offset.toUInt(&ok1, 16);
    auto length = _length.toUInt(&ok2, 16);
    if (!ok1 || !ok2) return {};
    return _calldata(stack, memory, offset, length);
}

QString Return::description()
{
    return "return memory[offset:offset+length]";
}

std::vector<std::pair<QString, QString> > Return::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "length", *(++iter) } };
}

QString DelegateCall::description()
{
    return "calls a method in another contract, using the storage of the current contract and returns success; memory[retOffset:retOffset+retLength] = address(addr).delegatecall.gas(gas) (memory[argsOffset:argsOffset+argsLength])";
}

std::vector<std::pair<QString, QString> > DelegateCall::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 6) return {};
    auto iter = stack.rbegin();
    return { { "gas", *iter }, { "addr", *(++iter) }, { "argsOffset", *(++iter) }, { "argsLength", *(++iter) }, { "retOffset", *(++iter) }, { "retLength", *(++iter) } };
}

QString DelegateCall::callsContract(const std::vector<QString> &stack, QString arg)
{
    if(stack.size() < 1) return "0x";
    auto iter = stack.rbegin();
    return "0x" + *(++iter);
}

Model::Calldata DelegateCall::calldata(const std::vector<QString> &stack, const std::vector<QString> &memory)
{
    if (stack.size() < 6) return {};
    auto iter = stack.rbegin();
    auto _offset = *(iter+2);
    auto _length = *(iter+3);
    bool ok1, ok2;
    auto offset = _offset.toUInt(&ok1, 16);
    auto length = _length.toUInt(&ok2, 16);
    if (!ok1 || !ok2) return {};
    return _calldata(stack, memory, offset, length);
}

QString Create2::description()
{
    return "creates a child contract with a deterministic address and returns its address; addr = new memory[offset:offset+length].value(value)";
}

std::vector<std::pair<QString, QString> > Create2::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 4) return {};
    auto iter = stack.rbegin();
    return { { "value", *iter }, { "offset", *(++iter) }, { "length", *(++iter) }, { "salt", *(++iter) } };
}

QString Create2::callsContract(const std::vector<QString> &stack, QString arg)
{
    if(stack.size() < 4) return "0x";
    auto iter = stack.rbegin();
    return "new contract at 0x" + *(iter + 3);
}

Model::Calldata Create2::calldata(const std::vector<QString> &stack, const std::vector<QString> &memory)
{
    if (stack.size() < 4) return {};
    auto iter = stack.rbegin();
    auto _offset = *(iter+1);
    auto _length = *(iter+2);
    bool ok1, ok2;
    auto offset = _offset.toUInt(&ok1, 16);
    auto length = _length.toUInt(&ok2, 16);
    if (!ok1 || !ok2) return {};
    return _calldata(stack, memory, offset, length);
}


QString StaticCall::description()
{
    return "calls a method in another contract and returns success, state changes such as contract creation, event emission, storage modification and contract destruction disallowed; memory[retOffset:retOffset+retLength] = address(addr).staticcall.gas(gas) (memory[argsOffset:argsOffset+argsLength])";
}

std::vector<std::pair<QString, QString> > StaticCall::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 6) return {};
    auto iter = stack.rbegin();
    return { { "gas", *iter }, { "addr", *(++iter) }, { "argsOffset", *(++iter) }, { "argsLength", *(++iter) }, { "retOffset", *(++iter) }, { "retLength", *(++iter) } };
}

QString StaticCall::callsContract(const std::vector<QString> &stack, QString arg)
{
    if(stack.size() < 1) return "0x";
    auto iter = stack.rbegin();
    return "0x" + *(++iter);
}

Model::Calldata StaticCall::calldata(const std::vector<QString> &stack, const std::vector<QString> &memory)
{
    if (stack.size() < 6) return {};
    auto iter = stack.rbegin();
    auto _offset = *(iter+2);
    auto _length = *(iter+3);
    bool ok1, ok2;
    auto offset = _offset.toUInt(&ok1, 16);
    auto length = _length.toUInt(&ok2, 16);
    if (!ok1 || !ok2) return {};
    return _calldata(stack, memory, offset, length);
}

QString Revert::description()
{
    return "revert(memory[offset:offset+length])";
}

std::vector<std::pair<QString, QString> > Revert::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 2) return {};
    auto iter = stack.rbegin();
    return { { "offset", *iter }, { "length", *(++iter) } };
}

QString SelfDestruct::description()
{
    return "sends all funds to addr and destroys the contract";
}

std::vector<std::pair<QString, QString> > SelfDestruct::functionArgs(const std::vector<QString> &stack, const QString &arg)
{
    if(stack.size() < 1) return {};
    auto iter = stack.rbegin();
    return { { "addr", *iter } };
}




