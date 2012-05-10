#ifndef CMESSAGE_H
#define CMESSAGE_H
#include <QString>
#include "CEnum.h"

class CMessage
{
public:
    CMessage();

    QString     m_Source;
    QString     m_Destinataire;
    QString     m_Message;
    QString     m_Attachement;
    CodeMessage m_CodeMessage;

};

#endif // CMESSAGE_H
