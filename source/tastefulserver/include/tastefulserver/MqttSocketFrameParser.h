#pragma once

#include <tastefulserver/tastefulserver_api.h>

#include <tastefulserver/ByteStream.h>
#include <tastefulserver/MqttSocketFrame.h>

#include <QObject>
#include <QQueue>
#include <QByteArray>
#include <array>

namespace tastefulserver {

class TASTEFULSERVER_API MqttSocketFrameParser : public QObject
{
    Q_OBJECT
public:
    MqttSocketFrameParser();

    void addData(const QByteArray & data);

    bool hasReadyFrames() const;
    MqttSocketFrame popReadyFrame();

signals:
    void badFrame();

protected:
    enum class ParseState
    {
        Header,
        LengthMask,
        ExtendedLength,
        Mask,
        Content,
        Finish,
        Error,
        Interrupted
    };

    ByteStream m_byteStream;
    MqttSocketFrame m_currentFrame;
    ParseState m_state;
    ParseState m_interruptedState;
    QQueue<MqttSocketFrame> m_readyFrames;

    void parse();

    ParseState dispatch(ParseState state);

    ParseState parseFrameHeader();
    ParseState parseLengthMask();
    ParseState parseExtendedLength();
    ParseState parseMask();
    ParseState parseContent();
    ParseState finishFrame();
    ParseState handleError();

    void pushFrame();

    qint64 length;
    MqttSocketFrame::LengthMask lengthMask;
    std::array<char, 4> mask;
};

} // namespace tastefulserver
