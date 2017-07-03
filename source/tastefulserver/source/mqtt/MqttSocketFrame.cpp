#include <tastefulserver/MqttSocketFrame.h>

#include <QDataStream>
#include <QtEndian>

#include <limits>
#include <cstring>

namespace tastefulserver {

const unsigned char MqttSocketFrame::Length2Bytes = 126;
const unsigned char MqttSocketFrame::Length4Bytes = 127;

MqttSocketFrame::MqttSocketFrame()
: m_masked(false)
{
    m_header.raw = 0;
}

MqttSocketFrame::MqttSocketFrame(const Header & header)
: m_header(header)
, m_masked(false)
{
}

MqttSocketFrame::MqttSocketFrame(OpCode opCode, bool isFinal)
: m_masked(false)
{
    m_header.raw = 0;
    m_header.data.opcode = (unsigned int)opCode;
    m_header.data.fin = isFinal ? 1 : 0;
}

MqttSocketFrame::MqttSocketFrame(OpCode opCode, const QByteArray & content)
: MqttSocketFrame(opCode, true)
{
    setContent(content);
}

void MqttSocketFrame::setHeader(const Header & header)
{
    m_header = header;
}

const MqttSocketFrame::Header & MqttSocketFrame::getHeader() const
{
    return m_header;
}

void MqttSocketFrame::setContent(const QByteArray & content)
{
    m_content = content;
}

const QByteArray & MqttSocketFrame::getContent() const
{
    return m_content;
}

void MqttSocketFrame::append(const QByteArray & data)
{
    m_content.append(data);
}

void MqttSocketFrame::setMask(const std::array<char, 4> & mask)
{
    m_masked = true;

    m_mask = mask;
}

void MqttSocketFrame::setMask(int mask)
{
    m_masked = true;

    m_mask = *reinterpret_cast<decltype(m_mask)*>(&mask);
}

void MqttSocketFrame::setRandomMask()
{
    setMask(qrand());
}

MqttSocketFrame::OpCode MqttSocketFrame::getOpCode() const
{
    return static_cast<OpCode>(m_header.data.opcode);
}

bool MqttSocketFrame::isControlFrame() const
{
    return getOpCode() >= OpCode::ConnectionClose;
}

bool MqttSocketFrame::isFinal() const
{
    return m_header.data.fin == 1;
}

bool MqttSocketFrame::isContinuationFrame() const
{
    return getOpCode() == OpCode::Continuation;
}

void MqttSocketFrame::writeTo(QIODevice & device) const
{
    device.write(toByteArray());
}

QByteArray MqttSocketFrame::toByteArray() const
{
    int headerLength = 2;
    qint64 contentLength = m_content.length();

    LengthMask lengthMask;

    if (contentLength < Length2Bytes)
    {
        lengthMask.data.len = contentLength;
    }
    else if (contentLength < std::numeric_limits<qint16>::max())
    {
        lengthMask.data.len = Length2Bytes;
        headerLength = 4;
    }
    else
    {
        lengthMask.data.len = Length4Bytes;
        headerLength = 10;
    }

    if (m_masked)
    {
        lengthMask.data.mask = 1;
        headerLength += 4;
    }
    else
    {
        lengthMask.data.mask = 0;
    }

    qint64 totalLength = headerLength + contentLength;

    // write data

    QByteArray byteArray(totalLength, 0);

    byteArray[0] = m_header.raw;
    byteArray[1] = lengthMask.raw;

    if (lengthMask.data.len == Length2Bytes)
    {
        qint16 len = qToBigEndian(static_cast<qint16>(contentLength));
        memcpy(&byteArray.data()[2], &len, sizeof((len)));
    }
    else if (lengthMask.data.len == Length4Bytes)
    {
        qint64 len = qToBigEndian(static_cast<qint64>(contentLength));
        memcpy(&byteArray.data()[2], &len, sizeof(len));
    }

    if (m_masked)
    {
        memcpy(&byteArray.data()[headerLength-4], &m_mask, 4);

        for (int i = 0; i < contentLength; ++i)
        {
            byteArray[headerLength + i] = (m_content[i] ^ m_mask[i % 4]);
        }
    }
    else
    {
        memcpy(&byteArray.data()[headerLength], m_content.data(), m_content.size());
    }

    return byteArray;
}

} // namespace tastefulserver
