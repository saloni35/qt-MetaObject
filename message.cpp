#include "message.h"

Message::Message()
{
    m_body = "Colour or Button not selected";
}

QString Message::body()
{
    return m_body;
}
