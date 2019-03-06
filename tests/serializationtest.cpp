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

#include "serializationtest.h"

#include "simpleintmessage.h"
#include "simplefloatmessage.h"
#include "simpledoublemessage.h"
#include "simplestringmessage.h"
#include "complexmessage.h"

using namespace qtprotobuf::tests;

SerializationTest::SerializationTest()
{
}

TEST_F(SerializationTest, IntMessageSrializeTest)
{
    SimpleIntMessage test;
    test.setTestFieldInt(15);
    QByteArray result = test.serialize();
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x1e');

    test.setTestFieldInt(300);
    result = test.serialize();
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xd8');
    ASSERT_EQ(result.at(2), '\x04');

    test.setTestFieldInt(65545);
    result = test.serialize();
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x92');
    ASSERT_EQ(result.at(2), '\x80');
    ASSERT_EQ(result.at(3), '\x08');

    test.setTestFieldInt(0);
    result = test.serialize();
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x00');

    test.setTestFieldInt(INT8_MAX + 1);
    result = test.serialize();
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x80');
    ASSERT_EQ(result.at(2), '\x02');

    test.setTestFieldInt(INT16_MAX + 1);
    result = test.serialize();
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x80');
    ASSERT_EQ(result.at(2), '\x80');
    ASSERT_EQ(result.at(3), '\x04');

    test.setTestFieldInt(INT8_MAX);
    result = test.serialize();
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xfe');
    ASSERT_EQ(result.at(2), '\x01');

    test.setTestFieldInt(INT16_MAX);
    result = test.serialize();
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xfe');
    ASSERT_EQ(result.at(2), '\xff');
    ASSERT_EQ(result.at(3), '\x03');

    test.setTestFieldInt(INT32_MAX);
    result = test.serialize();
    ASSERT_EQ(result.size(), 6);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xfe');
    ASSERT_EQ(result.at(2), '\xff');
    ASSERT_EQ(result.at(3), '\xff');
    ASSERT_EQ(result.at(4), '\xff');
    ASSERT_EQ(result.at(5), '\x0f');

    test.setTestFieldInt(-1);
    result = test.serialize();
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x01');

    test.setTestFieldInt(-462);
    result = test.serialize();
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x9b');
    ASSERT_EQ(result.at(2), '\x07');

    test.setTestFieldInt(-63585);
    result = test.serialize();
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xc1');
    ASSERT_EQ(result.at(2), '\xe1');
    ASSERT_EQ(result.at(3), '\x07');


    test.setTestFieldInt(INT8_MIN);
    result = test.serialize();
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xff');
    ASSERT_EQ(result.at(2), '\x01');

    test.setTestFieldInt(INT16_MIN);
    result = test.serialize();
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xff');
    ASSERT_EQ(result.at(2), '\xff');
    ASSERT_EQ(result.at(3), '\x03');

    test.setTestFieldInt(INT32_MIN);
    result = test.serialize();
    ASSERT_EQ(result.size(), 6);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\xff');
    ASSERT_EQ(result.at(2), '\xff');
    ASSERT_EQ(result.at(3), '\xff');
    ASSERT_EQ(result.at(4), '\xff');
    ASSERT_EQ(result.at(5), '\x0f');

    test.setTestFieldInt(INT8_MIN - 1);
    result = test.serialize();
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x81');
    ASSERT_EQ(result.at(2), '\x02');

    test.setTestFieldInt(INT16_MIN - 1);
    result = test.serialize();
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result.at(0), 0x08);
    ASSERT_EQ(result.at(1), '\x81');
    ASSERT_EQ(result.at(2), '\x80');
    ASSERT_EQ(result.at(3), '\x04');
}

TEST_F(SerializationTest, FloatMessageSrializeTest)
{
    constexpr int FloatMessageSize = 5;
    SimpleFloatMessage test;
    test.setTestFieldFloat(0.1f);
    QByteArray result = test.serialize();
    ASSERT_EQ(result.size(), FloatMessageSize);
    ASSERT_EQ(result.at(0), 0x3d);
    ASSERT_EQ(result.at(1), '\xcd');
    ASSERT_EQ(result.at(2), '\xcc');
    ASSERT_EQ(result.at(3), '\xcc');
    ASSERT_EQ(result.at(4), '\x3d');

    test.setTestFieldFloat(FLT_MIN);
    result = test.serialize();
    ASSERT_EQ(result.size(), FloatMessageSize);
    ASSERT_EQ(result.at(0), 0x3d);
    ASSERT_EQ(result.at(1), '\x00');
    ASSERT_EQ(result.at(2), '\x00');
    ASSERT_EQ(result.at(3), '\x80');
    ASSERT_EQ(result.at(4), '\x00');

    test.setTestFieldFloat(FLT_MAX);
    result = test.serialize();
    ASSERT_EQ(result.size(), FloatMessageSize);
    ASSERT_EQ(result.at(0), 0x3d);
    ASSERT_EQ(result.at(1), '\xff');
    ASSERT_EQ(result.at(2), '\xff');
    ASSERT_EQ(result.at(3), '\x7f');
    ASSERT_EQ(result.at(4), '\x7f');

    test.setTestFieldFloat(-4.2f);
    result = test.serialize();
    ASSERT_EQ(result.size(), FloatMessageSize);
    ASSERT_EQ(result.at(0), 0x3d);
    ASSERT_EQ(result.at(1), '\x66');
    ASSERT_EQ(result.at(2), '\x66');
    ASSERT_EQ(result.at(3), '\x86');
    ASSERT_EQ(result.at(4), '\xc0');

    test.setTestFieldFloat(-0.0f);
    result = test.serialize();
    ASSERT_EQ(result.size(), FloatMessageSize);
    ASSERT_EQ(result.at(0), 0x3d);
    ASSERT_EQ(result.at(1), '\x00');
    ASSERT_EQ(result.at(2), '\x00');
    ASSERT_EQ(result.at(3), '\x00');
    ASSERT_EQ(result.at(4), '\x80');
}

TEST_F(SerializationTest, DoubleMessageSrializeTest)
{
    constexpr int DoubleMessageSize = 9;
    SimpleDoubleMessage test;
    test.setTestFieldDouble(0.1);
    QByteArray result = test.serialize();
    ASSERT_EQ(result.size(), DoubleMessageSize);
    ASSERT_EQ(result.at(0), 0x41);
    ASSERT_EQ(result.at(1), '\x9a');
    ASSERT_EQ(result.at(2), '\x99');
    ASSERT_EQ(result.at(3), '\x99');
    ASSERT_EQ(result.at(4), '\x99');
    ASSERT_EQ(result.at(5), '\x99');
    ASSERT_EQ(result.at(6), '\x99');
    ASSERT_EQ(result.at(7), '\xb9');
    ASSERT_EQ(result.at(8), '\x3f');

    test.setTestFieldDouble(DBL_MIN);
    result = test.serialize();
    ASSERT_EQ(result.size(), DoubleMessageSize);
    ASSERT_EQ(result.at(0), 0x41);
    ASSERT_EQ(result.at(1), '\x00');
    ASSERT_EQ(result.at(2), '\x00');
    ASSERT_EQ(result.at(3), '\x00');
    ASSERT_EQ(result.at(4), '\x00');
    ASSERT_EQ(result.at(5), '\x00');
    ASSERT_EQ(result.at(6), '\x00');
    ASSERT_EQ(result.at(7), '\x10');
    ASSERT_EQ(result.at(8), '\x00');

    test.setTestFieldDouble(DBL_MAX);
    result = test.serialize();
    ASSERT_EQ(result.size(), DoubleMessageSize);
    ASSERT_EQ(result.at(0), 0x41);
    ASSERT_EQ(result.at(1), '\xff');
    ASSERT_EQ(result.at(2), '\xff');
    ASSERT_EQ(result.at(3), '\xff');
    ASSERT_EQ(result.at(4), '\xff');
    ASSERT_EQ(result.at(5), '\xff');
    ASSERT_EQ(result.at(6), '\xff');
    ASSERT_EQ(result.at(7), '\xef');
    ASSERT_EQ(result.at(8), '\x7f');

    test.setTestFieldDouble(-4.2);
    result = test.serialize();
    ASSERT_EQ(result.size(), DoubleMessageSize);
    ASSERT_EQ(result.at(0), 0x41);
    ASSERT_EQ(result.at(1), '\xcd');
    ASSERT_EQ(result.at(2), '\xcc');
    ASSERT_EQ(result.at(3), '\xcc');
    ASSERT_EQ(result.at(4), '\xcc');
    ASSERT_EQ(result.at(5), '\xcc');
    ASSERT_EQ(result.at(6), '\xcc');
    ASSERT_EQ(result.at(7), '\x10');
    ASSERT_EQ(result.at(8), '\xc0');

    test.setTestFieldDouble(0.0);
    result = test.serialize();
    ASSERT_EQ(result.size(), DoubleMessageSize);
    ASSERT_EQ(result.at(0), 0x41);
    ASSERT_EQ(result.at(1), '\x00');
    ASSERT_EQ(result.at(2), '\x00');
    ASSERT_EQ(result.at(3), '\x00');
    ASSERT_EQ(result.at(4), '\x00');
    ASSERT_EQ(result.at(5), '\x00');
    ASSERT_EQ(result.at(6), '\x00');
    ASSERT_EQ(result.at(7), '\x00');
    ASSERT_EQ(result.at(8), '\x00');
}

TEST_F(SerializationTest, StringMessageSerializeTest)
{
    SimpleStringMessage test;
    test.setTestFieldString("qwerty");
    QByteArray result = test.serialize();
    ASSERT_TRUE(result == QByteArray::fromHex("3206717765727479"));

    test.setTestFieldString("oepSNLIVG08UJpk2W7JtTkkBxyK06X0lQ6ML7IMd55K8XC1Tpsc1kDWym5v8z68b4FQup9O95QSgAvjHIA15OX6Bu68esbQFT9LPzSADJ6qSGBTYBHX5QSZg32trCdHMj80XuDHqyBgM4uf6RKq2mgWb8Ovxxr0NwLxjHOfhJ8Mrfd2R7hbUgjespbYoQhbgHEj2gKEV3QvnumYmrVXe1BkCzZhKVXodDhj0OfAE67viAy4i3Oag1hr1z4Azo8O5Xq68POEZ1CsZPo2DXNNR8ebVCdYOz0Q6JLPSl5jasLCFrQN7EiVNjQmCrSsZHRgLNylvgoEFxGYxXJ9gmK4mr0OGdZcGJORRGZOQCpQMhXmhezFalNIJXMPPXaRVXiRhRAPCNUEie8DtaCWAMqz4nNUxRMZ5UcXBXsXPshygzkyyXnNWTIDojFlrcsnKqSkQ1G6E85gSZbtIYBh7sqO6GDXHjOrXVaVCVCUubjcJKThlyslt29zHuIs5JGppXxX1");
    result = test.serialize();
    ASSERT_TRUE(result == QByteArray::fromHex("3280046f6570534e4c4956473038554a706b3257374a74546b6b4278794b303658306c51364d4c37494d6435354b3858433154707363316b4457796d3576387a3638623446517570394f393551536741766a48494131354f583642753638657362514654394c507a5341444a367153474254594248583551535a67333274724364484d6a383058754448717942674d34756636524b71326d675762384f76787872304e774c786a484f66684a384d726664325237686255676a65737062596f5168626748456a32674b45563351766e756d596d7256586531426b437a5a684b56586f6444686a304f6641453637766941793469334f6167316872317a34417a6f384f3558713638504f455a3143735a506f3244584e4e52386562564364594f7a3051364a4c50536c356a61734c434672514e374569564e6a516d437253735a4852674c4e796c76676f454678475978584a39676d4b346d72304f47645a63474a4f5252475a4f514370514d68586d68657a46616c4e494a584d50505861525658695268524150434e55456965384474614357414d717a346e4e5578524d5a355563584258735850736879677a6b7979586e4e575449446f6a466c7263736e4b71536b5131473645383567535a6274495942683773714f36474458486a4f72585661564356435575626a634a4b54686c79736c7432397a48754973354a47707058785831"));
}

TEST_F(SerializationTest, ComplexTypeSerializeTest)
{
    qRegisterMetaType<SimpleStringMessage>("SimpleStringMessage");
    SimpleStringMessage stringMsg;
    stringMsg.setTestFieldString("qwerty");

    ComplexMessage test;
    test.setTestFieldInt(42);
    test.setTestComplexField(stringMsg);

    QByteArray result = test.serialize();
    ASSERT_TRUE(result == QByteArray::fromHex("120832067177657274790854"));


    stringMsg.setTestFieldString("YVRfJvjxqbgvFwS1YvOZXgtj5ffGLS7AiNHz9oZIoKbm7z8H79xBuyPkpQXvGoO09OY9xRawx3eOAs9xjoTA1xJhrw28TAcq1CebYlC9WUfQC6hIantaNdyHiKToffi0Zt7la42SRxXZSP4GuxbcZIp53pJnyCwfCy1qdFczT0dmn7h8fpyAdemEavwFeda4d0PApGfSU2jLt39X8kYUBxNM2WgALRBgHdVde87q6Pi5U69TjhMd28W1SFD1DxyogCCrqOct2ZPICoLnrqdF3OdNzjRVLfeyvQ8LgLvRNFR9WfWAyAz79nKgBamd8Ntlvt4Mg35E5gVS2g7AQ7rkm72cBdnW9sCEyGabeXAuH5j4GRbuLT7qBZWDcFLF4SsCdS3WfFGdNHfwaijzykByo71PvFVlTXH2WJWoFvR5FALjBTn7bCdP0pAiSbLCY8Xz2Msc3dBb5Ff9GISPbUpNmUvBdMZMHQvqOmTNXEPpN0b74MDOMQfWJShOo3NkAvMjs");
    test.setTestFieldInt(42);
    test.setTestComplexField(stringMsg);

    result = test.serialize();
    ASSERT_TRUE(result == QByteArray::fromHex("128404328104595652664a766a78716267764677533159764f5a5867746a356666474c533741694e487a396f5a496f4b626d377a3848373978427579506b70515876476f4f30394f5939785261777833654f417339786a6f544131784a68727732385441637131436562596c43395755665143366849616e74614e647948694b546f666669305a74376c613432535278585a53503447757862635a49703533704a6e79437766437931716446637a5430646d6e3768386670794164656d456176774665646134643050417047665355326a4c74333958386b595542784e4d325767414c524267486456646538377136506935553639546a684d6432385731534644314478796f67434372714f6374325a5049436f4c6e72716446334f644e7a6a52564c6665797651384c674c76524e4652395766574179417a37396e4b6742616d64384e746c7674344d6733354535675653326737415137726b6d37326342646e5739734345794761626558417548356a34475262754c543771425a574463464c463453734364533357664647644e48667761696a7a796b42796f3731507646566c54584832574a576f4676523546414c6a42546e37624364503070416953624c435938587a324d73633364426235466639474953506255704e6d557642644d5a4d485176714f6d544e584550704e306237344d444f4d5166574a53684f6f334e6b41764d6a730854"));


    stringMsg.setTestFieldString("qwerty");
    test.setTestFieldInt(-45);
    test.setTestComplexField(stringMsg);

    result = test.serialize();
    ASSERT_TRUE(result == QByteArray::fromHex("120832067177657274790859"));
}