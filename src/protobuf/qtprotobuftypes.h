/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of qtprotobuf project https://git.semlanik.org/semlanik/qtprotobuf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <qglobal.h>
#include <QList>
#include <QMetaType>

namespace qtprotobuf {

enum WireTypes {
    UnknownWireType = -1,
    Varint = 0,
    Fixed64 = 1,
    LengthDelimited = 2,
    Fixed32 = 5
};

constexpr int NotUsedFieldIndex = -1;

template<typename T, int = 0>
struct transparent {
    transparent(T t = T()) : _t(t){}
    T _t;
    operator T&(){ return _t; }
    operator T() const { return _t; }
};

using int32 = int32_t;
using int64 = int64_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using sint32 = transparent<int32_t>;
using sint64 = transparent<int64_t>;
using fint32 = transparent<uint32_t, 1>;
using fint64 = transparent<uint64_t, 1>;
using sfint32 = transparent<int32_t, 1>;
using sfint64 = transparent<int64_t, 1>;

using int32List = QList<int32>;
using int64List = QList<int64>;
using uint32List = QList<uint32>;
using uint64List = QList<uint64>;
using sint32List = QList<sint32>;
using sint64List = QList<sint64>;
using fint32List = QList<fint32>;
using fint64List = QList<fint64>;
using sfint32List = QList<sfint32>;
using sfint64List = QList<sfint64>;

using FloatList = QList<float>;
using DoubleList = QList<double>;
}

Q_DECLARE_METATYPE(qtprotobuf::int32)
Q_DECLARE_METATYPE(qtprotobuf::int64)
Q_DECLARE_METATYPE(qtprotobuf::sint32)
Q_DECLARE_METATYPE(qtprotobuf::sint64)
Q_DECLARE_METATYPE(qtprotobuf::uint32)
Q_DECLARE_METATYPE(qtprotobuf::uint64)
Q_DECLARE_METATYPE(qtprotobuf::fint32)
Q_DECLARE_METATYPE(qtprotobuf::fint64)
Q_DECLARE_METATYPE(qtprotobuf::sfint32)
Q_DECLARE_METATYPE(qtprotobuf::sfint64)

Q_DECLARE_METATYPE(qtprotobuf::int32List)
Q_DECLARE_METATYPE(qtprotobuf::int64List)
Q_DECLARE_METATYPE(qtprotobuf::sint32List)
Q_DECLARE_METATYPE(qtprotobuf::sint64List)
Q_DECLARE_METATYPE(qtprotobuf::uint32List)
Q_DECLARE_METATYPE(qtprotobuf::uint64List)
Q_DECLARE_METATYPE(qtprotobuf::fint32List)
Q_DECLARE_METATYPE(qtprotobuf::fint64List)
Q_DECLARE_METATYPE(qtprotobuf::sfint32List)
Q_DECLARE_METATYPE(qtprotobuf::sfint64List)

Q_DECLARE_METATYPE(qtprotobuf::FloatList)
Q_DECLARE_METATYPE(qtprotobuf::DoubleList)