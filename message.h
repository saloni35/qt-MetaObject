    #ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QMetaType>

class Message
{
public:
    Message();    
    QString body();

private:
    QString m_body;
};

Q_DECLARE_METATYPE(Message);

#endif // MESSAGE_H
