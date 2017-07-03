#include <tastefulserver/MqttSocket.h>

#include <tastefulserver/MqttSocketHandler.h>
#include <tastefulserver/HttpSocket.h>

#include <QCryptographicHash>
#include <QTcpSocket>
#include <QAbstractSocket>

namespace tastefulserver {

MqttSocket::MqttSocket(MqttSocketHandler * handler)
: m_handler(handler)
{
    connect(&m_parser, &MqttSocketFrameParser::badFrame, this, &MqttSocket::badFrame);
}

QAbstractSocket * MqttSocket::createSocket(qintptr socketDescriptor)
{
    QTcpSocket * socket = new QTcpSocket();

    socket->setSocketDescriptor(socketDescriptor);

    return socket;
}



void MqttSocket::receiveData(const QByteArray & data)
{
    m_parser.addData(data);

    while (m_parser.hasReadyFrames())
    {
        MqttSocketFrame frame = m_parser.popReadyFrame();
#if 0
        if (!frame.isFinal())
        {
            if (frame.isControlFrame())
            {
                disconnect();
                break;
            }

            if (!m_inFragmentedMode)
            {
                m_inFragmentedMode = true;
                m_fragmentedMessage = frame;
            }
            else
            {
                if (!frame.isContinuationFrame())
                {
                    disconnect();
                    break;
                }

                m_fragmentedMessage.append(frame.getContent());
            }

            continue;
        }

        if (frame.isContinuationFrame())
        {
            if (!m_inFragmentedMode)
            {
                disconnect();
                break;
            }

            m_fragmentedMessage.append(frame.getContent());
            m_inFragmentedMode = false;

            frame = m_fragmentedMessage;
        }
#endif
        switch (frame.getOpCode())
        {
            case MqttSocketFrame::OpCode::Text:
                //m_handler->handleText(this, frame.getContent());
                break;
            case MqttSocketFrame::OpCode::Binary:
                //m_handler->handleBinary(this, frame.getContent());
                break;
            case MqttSocketFrame::OpCode::Ping:
                sendPong();
                break;
            case MqttSocketFrame::OpCode::Pong:
                break;
            case MqttSocketFrame::OpCode::ConnectionClose:
                sendFrame(MqttSocketFrame(MqttSocketFrame::OpCode::ConnectionClose));
                disconnect();
                break;
            default:
                break;
        }
    }
}

void MqttSocket::badFrame()
{
    disconnect();
}

void MqttSocket::sendFrame(const MqttSocketFrame & frame)
{
    frame.writeTo(*m_socket);
}

#if 0
void MqttSocket::sendText(const QByteArray & text)
{
    sendFrame(MqttSocketFrame(MqttSocketFrame::OpCode::Text, text));
}

void MqttSocket::sendBinary(const QByteArray & binary)
{
    sendFrame(MqttSocketFrame(MqttSocketFrame::OpCode::Binary, binary));
}

void MqttSocket::sendPing()
{
    sendFrame(MqttSocketFrame(MqttSocketFrame::OpCode::Ping));
}
#endif

void MqttSocket::sendPong()
{
    sendFrame(MqttSocketFrame(MqttSocketFrame::OpCode::Pong));
}

void MqttSocket::closeConnection()
{
    sendFrame(MqttSocketFrame(MqttSocketFrame::OpCode::ConnectionClose));
    disconnect();
}

void MqttSocket::connectionClosed()
{
    //m_handler->connectionClosed(m_request, this);
}

} // namespace tastefulserver
