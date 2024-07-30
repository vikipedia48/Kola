#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QHash>

namespace Model {

struct Calldata {
    std::vector<std::optional<QChar>> data;
    std::optional<int> size;
    QString stringRepresentation;

    Calldata(std::vector<std::optional<QChar>>&& data, std::optional<int> size) : data(data), size(size), stringRepresentation("") {
        setStringRepresentation();
    }
    void setStringRepresentation() {
        // function selector
        stringRepresentation += fromCalldataChars(this->data, 0, 8);

        // arguments
        for(auto i = 8; i < this->data.size(); i+=64) {
            stringRepresentation += fromCalldataChars(this->data, i, 64);
        }

        // if calldatasize is explicitly known, resize the calldata
        if (this->size.has_value()) {
            stringRepresentation.resize(this->size.value() * 2, '?');
        }
    }
    void setByte(uint32_t index, QChar byte)
    {
        if (index >= data.size()) {
            data.resize(index + 1);
        }
        data[index] = byte;
    }
    Calldata() {}
private:
    QString fromCalldataChars(const std::vector<std::optional<QChar>>& data, int startIndex, int length) {
        auto rv = QString(length+1, '?');
        auto dataSize = data.size();
        for(int i = 0; i < length; ++i) {
            if (startIndex + i >= dataSize) break;
            auto character = data[startIndex+i];
            if (character.has_value()) {
                rv[i] = character.value();
            }
        }
        rv[length] = '\n';
        return rv;
    }
};

struct ExecutingContract {
    QString title;
    int firstOperationIndex;
    int lastOperationIndex;
    Calldata calldata;
    bool isMain;
    bool failed;
    int depth;
    ExecutingContract(QString title, int firstOperationIndex, int depth, Calldata calldata = {}) : title(title), firstOperationIndex(firstOperationIndex), depth(depth), isMain(depth == 1), calldata(calldata), failed(false) {}
};

struct StorageSlot {
    QString address;
    QString word;
    bool hasBeenAltered;
    size_t hash;

    StorageSlot(QString address, QString word, bool hasBeenAltered) : address(address), word(word), hasBeenAltered(hasBeenAltered) {
        hash = qHash(address, qHash(word));
    }
    StorageSlot() {}
    bool operator==(const StorageSlot& rhs) const { return hash == rhs.hash; }
};
struct StepStorage {
    std::vector<StorageSlot> _slots;
    std::optional<int> hasBeenChanged;
    std::optional<int> willBeChanged;
    StepStorage(std::vector<StorageSlot>&& blocks, std::optional<int> hasBeenChanged, std::optional<int> willbeChanged) :
        _slots(blocks), hasBeenChanged(hasBeenChanged), willBeChanged(willbeChanged) {}
};
struct ArrayItem {
    QString title;
    size_t hash;
    ArrayItem(const QString& title) : title(title) { hash = qHash(title); }
    bool operator==(const ArrayItem& rhs) { return hash == rhs.hash; }
    bool operator!=(const ArrayItem& rhs) { return hash != rhs.hash; }
};

struct Range {
    int start;
    int end;
    Range(int start, int end) : start(start), end(end) {}
};
struct StepMemory {
    std::vector<ArrayItem> blocks;
    std::optional<Range> hasBeenChanged;
    std::optional<Range> willBeChanged;
    StepMemory(std::vector<QString>&& _blocks, std::optional<Range> hasBeenChanged, std::optional<Range> willBeChanged) : hasBeenChanged(hasBeenChanged), willBeChanged(willBeChanged) {
        for(auto&& v : _blocks) {
            blocks.emplace_back(ArrayItem(v));
        }
    }
};
struct StepStack {
    std::vector<QString> _slots;
    std::optional<int> ofNotice;
    int numberOfPops;

    StepStack(std::vector<QString>&& blocks, std::optional<int> ofNotice, int numberOfPops) : _slots(blocks), ofNotice(ofNotice), numberOfPops(numberOfPops) {}
};
struct OperationArgument {
    QString name;
    QString value;
    QString tooltip;

    OperationArgument(QString name, QString value) : name(name), value(value) {
        if (value.length() != 64) return;
        auto bytes = QByteArray(32, '?');
        bool largerThanUint64 = false;
        for(int i = 0; i < 64; i += 2) {
            auto hex = value.mid(i, 2);
            auto number = hex.toUInt(nullptr, 16);
            if (number > 0 && i < 48) largerThanUint64 = true;
            bytes[i/2] = static_cast<unsigned char>(number);
        }
        tooltip = "utf8: " + QString::fromUtf8(bytes);
        if (largerThanUint64) {
            tooltip += "\nuint: " + QString::number(bytes.toULong()) + "\nint: " + QString::number(bytes.toLong());
        }
    }
};
struct StepInfo {
    QString opcode;
    QString description;
    std::vector<OperationArgument> params;
    int index;
    QString indexStr;
    uint64_t pc;
    QString pcStr;
    uint64_t gasLeft;
    QString gasLeftStr;
    uint64_t gasCost;
    QString gasCostStr;
    std::optional<QString> errorReason;
    int threadIndex;
    std::optional<QString> newValuePushed;

    StepInfo(QString opcode, QString description, std::vector<OperationArgument>&& params, int index, uint64_t pc, uint64_t gasLeft, uint64_t gasCost, int threadIndex, std::optional<QString> errorReason, std::optional<QString> newValuePushed)
        : opcode(opcode), description(description), params(params),
        index(index), indexStr(QString::number(index)),
        pc(pc), pcStr(QString::number(pc)),
        gasLeft(gasLeft), gasLeftStr(QString::number(gasLeft)),
        gasCost(gasCost), gasCostStr(QString::number(gasCost)),
        threadIndex(threadIndex),
        errorReason(errorReason),
        newValuePushed(newValuePushed)
        {}
};
}
namespace std {
    template<> struct hash<Model::StorageSlot> {
        std::size_t operator()(const Model::StorageSlot& obj) const {
            return obj.hash;
        }
    };
}

#endif // MODEL_H
