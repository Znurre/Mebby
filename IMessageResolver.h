#ifndef IMESSAGERESOLVER_H
#define IMESSAGERESOLVER_H

#include <QDataStream>

class MessageWriter;

class IMessageResolver
{
	public:
		virtual quint8 type() const = 0;

		virtual void resolve(QDataStream &stream, MessageWriter &writer) const = 0;
};

#endif // IMESSAGERESOLVER_H
