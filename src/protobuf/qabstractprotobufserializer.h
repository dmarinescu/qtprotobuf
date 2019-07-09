/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of QtProtobuf project https://git.semlanik.org/semlanik/qtprotobuf
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

#include <QObject>
#include <QVariant>
#include <QMetaObject>

#include <unordered_map>
#include <functional>
#include <memory>

#include "qtprotobuftypes.h"
#include "qtprotobuflogging.h"
#include "qprotobufselfcheckiterator.h"

#include "qtprotobufglobal.h"

namespace QtProtobuf {
/*!
*  \addtogroup QtProtobuf
*  \{
*/

/*!
 * \brief The QAbstractProtobufSerializer class is interface that represents basic functions for serialization/deserialization
 *
 * \details The QAbstractProtobufSerializer class registers serializers/deserializers for classes inherited of QObject.
 *          To register serializers for user-defined class it has to be inherited of QObject and contains
 *          Q_DECLARE_PROTOBUF_SERIALIZERS macro's.
 *          \code{.cpp}
 *          class MyType : public QObject
 *          {
 *              Q_OBJECT
 *              Q_PROTOBUF_OBJECT
 *              Q_PROPERTY(qprotobuf::sint32 prop READ prop WRITE setProp NOTIFY propChanged)
 *              ...
 *              Q_DECLARE_PROTOBUF_SERIALIZERS(MyType)
 *          };
 *          \endcode
 *          Practically code above is generated automaticaly by running qtprotobufgenerator or using cmake build macro
 *          generate_qtprotobuf, based on .proto files. But it's still possible to reuse manually written code if needed.
 *
 *          This class should be used as base for specific serializers. The handlers property contains all
 *          message-specific serializers and should be used while serialization/deserialization. Inherited classes should reimplement
 *          scope of virtual methods that used by registred message serialization/deserialization functions.
 */
class Q_PROTOBUF_EXPORT QAbstractProtobufSerializer
{
public:
    /*!
     * \brief Serialization of a registered qtproto message object into byte-array
     *
     *
     * \param[in] object Pointer to QObject containing message to be serialized
     * \result serialized message bytes
     */
    template<typename T>
    QByteArray serialize(const QObject *object) {
        qProtoDebug() << T::staticMetaObject.className() << "serialize";
        return serializeMessage(object, T::propertyOrdering, T::staticMetaObject);
    }

    /*!
     * \brief Deserialization of a byte-array into a registered qtproto message object
     *
     * \details Properties in a message are identified via ProtobufObjectPrivate::decodeHeader.
     *          Bytes corresponding to unexpected properties are skipped without any exception
     *
     * \param[out] object Pointer to memory where result of deserialization should be injected
     * \param[in] array Bytes with serialized message
     */
    template<typename T>
    void deserialize(QObject *object, const QByteArray &array) {
        qProtoDebug() << T::staticMetaObject.className() << "deserialize";
        deserializeMessage(object, array, T::propertyOrdering, T::staticMetaObject);
    }

    virtual ~QAbstractProtobufSerializer() = default;

    /*!
     * \brief serializeMessage
     * \param object
     * \param propertyOrdering
     * \param metaObject
     * \return
     */
    virtual QByteArray serializeMessage(const QObject *object, const QProtobufPropertyOrdering &propertyOrdering, const QMetaObject &metaObject) const = 0;

    /*!
     * \brief serializeMessage
     * \param object
     * \param propertyOrdering
     * \param metaObject
     * \return
     */
    virtual void deserializeMessage(QObject *object, const QByteArray &data, const QProtobufPropertyOrdering &propertyOrdering, const QMetaObject &metaObject) const = 0;

    /*!
     * \brief serializeObject Serializes complete \a object according given \a propertyOrdering and \a metaObject
     *        information
     * \param[in] object Pointer to object to be serialized
     * \param[in] propertyOrdering Protobuf order of QObject properties
     * \param[in] metaObject Meta object information for given \a object
     * \return Raw serialized data represented as byte array
     */
    virtual QByteArray serializeObject(const QObject *object, const QProtobufPropertyOrdering &propertyOrdering, const QMetaObject &metaObject) const = 0;

    /*!
     * \brief deserializeObject Deserializes buffer to an \a object
     * \param[out] object Pointer to allocated object
     * \param[in] it Pointer to beging of buffer where object serialized data is located
     * \param[in] propertyOrdering Ordering of properties for given \a object
     * \param[in] metaObject Static meta object of given \a object. Static meta object usualy is used to get actual
     *        property value and write new property to \a object
     */
    virtual void deserializeObject(QObject *object, QProtobufSelfcheckIterator &it, const QProtobufPropertyOrdering &propertyOrdering, const QMetaObject &metaObject) const = 0;

    /*!
     * \brief serializeListObject Method called to serialize \a object as a part of list property
     * \param[in] object Pointer to object that will be serialized
     * \param[in] propertyOrdering Ordering of properties for given \a object
     * \param[in] metaObject Static meta object of given \a object
     * \param[in] fieldIndex Index of list property in target message
     * \return Raw serialized data represented as byte array
     */
    virtual QByteArray serializeListObject(const QObject *object, const QProtobufPropertyOrdering &propertyOrdering, const QMetaObject &metaObject, int fieldIndex) const = 0;

    /*!
     * \brief deserializeListObject Deserializes an \a object from byte stream as part of list property
     * \param[out] object Pointer to allocated object, that will be appended to list property
     * \param[in] it Pointer to beging of buffer where object serialized data is located
     * \param[in] propertyOrdering Ordering of properties for given \a object
     * \param[in] metaObject Static meta object of given \a object. Static meta object usualy is used to get actual
     *        property value and write new property to \a object
     */
    virtual void deserializeListObject(QObject *object, QProtobufSelfcheckIterator &it, const QProtobufPropertyOrdering &propertyOrdering, const QMetaObject &metaObject) const = 0;

    /*!
     * \brief serializeMapPair Serializes QMap pair of \a key and \a value to raw data buffer
     * \param[in] key Map key
     * \param[in] value Map value for given \a key
     * \param[in] fieldIndex Index of map property in message
     * \return Raw serialized data represented as byte array
     *
     * \see https://developers.google.com/protocol-buffers/docs/proto3#maps for details
     */
    virtual QByteArray serializeMapPair(const QVariant &key, const QVariant &value, int fieldIndex) const = 0;

    /*!
     * \brief deserializeMapPair Deserializes QMap pair of \a key and \a value from raw data
     * \param[out] key Buffer that will be used to store deserialized key. When passed to function, QVariant
     *        already stores default constructed value. So it's possible to receive meta information about type from it.
     * \param[out] value Buffer that will be used to store deserialized value. When passed to function, QVariant
     *        already stores default constructed value. So it's possible to receive meta information about type from it.
     * \param[in] it Points to serialized raw key/value data
     *
     * \see https://developers.google.com/protocol-buffers/docs/proto3#maps for details
     */
    virtual void deserializeMapPair(QVariant &key, QVariant &value, QProtobufSelfcheckIterator &it) const = 0;
};
/*! \} */
}

#include "qabstractprotobufserializer_p.h"

/*!
 * \brief Registers serializers for type T in QtProtobuf global serializers registry
 *
 * \details generates default serializers for type T. Type T has to be inherited of QObject.
 */
template<typename T>
static void qRegisterProtobufType() {
    QtProtobufPrivate::registerHandler(qMetaTypeId<T *>(), { QtProtobufPrivate::serializeComplexType<T>,
            QtProtobufPrivate::deserializeComplexType<T>, QtProtobuf::LengthDelimited });
    QtProtobufPrivate::registerHandler(qMetaTypeId<QList<QSharedPointer<T>>>(), { QtProtobufPrivate::serializeList<T>,
            QtProtobufPrivate::deserializeList<T>, QtProtobuf::LengthDelimited });
}

/*!
 * \brief Registers serializers for type QMap<K, V> in QtProtobuf global serializers registry
 *
 * \details generates default serializers for QMap<K, V>.
 */
template<typename K, typename V,
         typename std::enable_if_t<!std::is_base_of<QObject, V>::value, int> = 0>
inline void qRegisterProtobufMapType() {
    QtProtobufPrivate::registerHandler(qMetaTypeId<QMap<K, V>>(), { QtProtobufPrivate::serializeMap<K, V>,
    QtProtobufPrivate::deserializeMap<K, V>, QtProtobuf::LengthDelimited });
}

/*!
 * \brief Registers serializers for type QMap<K, V> in QtProtobuf global serializers registry
 *
 * \details generates default serializers for QMap<K, V>. Specialization for V type
 *          inherited of QObject.
 */
template<typename K, typename V,
         typename std::enable_if_t<std::is_base_of<QObject, V>::value, int> = 0>
inline void qRegisterProtobufMapType() {
    QtProtobufPrivate::registerHandler(qMetaTypeId<QMap<K, QSharedPointer<V>>>(), { QtProtobufPrivate::serializeMap<K, V>,
    QtProtobufPrivate::deserializeMap<K, V>, QtProtobuf::LengthDelimited });
}
