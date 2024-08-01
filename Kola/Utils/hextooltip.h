#ifndef HEXTOOLTIP_H
#define HEXTOOLTIP_H

#include <QString>


namespace HexTooltip {
    inline QString fromWord(QString value) {
        size_t valueSize = value.size();
        auto bytes = QByteArray(valueSize/2, '?');
        bool largerThanUint64 = false;
        for(int i = 0; i < value.size(); i += 2) {
            auto hex = value.mid(i, 2);
            auto number = hex.toUInt(nullptr, 16);
            if (number > 0 && valueSize - i > 16) largerThanUint64 = true;
            bytes[i/2] = static_cast<unsigned char>(number);
        }
        QString tooltip = "utf8: " + QString::fromUtf8(bytes);
        if (!largerThanUint64) {
            tooltip += "\nuint: " + QString::number(value.toULong(nullptr, 16)) + "\nint: " + QString::number(value.toLong(nullptr, 16));
        }
        return tooltip;
    }
    inline QString hexNumber(QString hexString) {
        bool ok;
        uint64_t number = hexString.toULong(&ok, 16);
        return ok ? QString::number(number) : "";
    }
    inline QString hexUtf8(QString value) {
        size_t valueSize = value.size();
        auto bytes = QByteArray(valueSize/2, '?');
        for(int i = 0; i < value.size(); i += 2) {
            auto hex = value.mid(i, 2);
            auto number = hex.toUInt(nullptr, 16);
            bytes[i/2] = static_cast<unsigned char>(number);
        }
        return "utf8: " + QString::fromUtf8(bytes);
    }
}

#endif // HEXTOOLTIP_H
