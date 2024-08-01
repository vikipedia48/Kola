#ifndef HEXTOOLTIP_H
#define HEXTOOLTIP_H

#include <QString>


namespace HexTooltip {
    QString fromWord(QString value) {
        if (value.length() != 64) return {};
        auto bytes = QByteArray(32, '?');
        bool largerThanUint64 = false;
        for(int i = 0; i < 64; i += 2) {
            auto hex = value.mid(i, 2);
            auto number = hex.toUInt(nullptr, 16);
            if (number > 0 && i < 48) largerThanUint64 = true;
            bytes[i/2] = static_cast<unsigned char>(number);
        }
        QString tooltip = "utf8: " + QString::fromUtf8(bytes);
        if (!largerThanUint64) {
            tooltip += "\nuint: " + QString::number(bytes.toULong()) + "\nint: " + QString::number(bytes.toLong());
        }
        return tooltip;
    }
    QString hexNumber(QString hexString) {
        bool ok;
        uint64_t number = hexString.toULong(&ok, 16);
        return ok ? QString::number(number) : "";
    }
}

#endif // HEXTOOLTIP_H
