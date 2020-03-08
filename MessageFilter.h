#ifndef MESSAGEFILTER_H
#define MESSAGEFILTER_H

#include <QObject>
#include <QWebSocket>
#include <QList>

#include "IMessageResolver.h"
#include "MessageResolver.h"

template<typename ...TMessage>
class IMessageCallbacks;

template<typename TMessage>
class IMessageCallback;

class MessageWriter;

class MessageFilter : public QObject
{
	public:
		template<typename ...TMessage>
		MessageFilter(IMessageCallbacks<TMessage...> &callbacks)
			: m_resolvers({ new MessageResolver<TMessage>(callbacks)... })
		{
		}

		void onBinaryMessageReceived(MessageWriter &writer, const QByteArray &message)
		{
			quint8 messageType;

			QDataStream stream(message);
			stream >> messageType;

			qDebug() << "DEBUG: Message of type" << messageType << "received";

			for (IMessageResolver *resolver : m_resolvers)
			{
				if (resolver->type() == messageType)
				{
					return resolver->resolve(stream, writer);
				}
			}
		}

	private:
		QList<IMessageResolver *> m_resolvers;
};

#endif // MESSAGEFILTER_H
