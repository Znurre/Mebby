#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QtGlobal>

template<quint8 TMessageType>
struct IMessage
{
	static const quint8 Type;
};

template <quint8 TMessageType>
const quint8 IMessage<TMessageType>::Type(TMessageType);

#endif // IMESSAGE_H
