#ifndef MESSAGERESOLVER_H
#define MESSAGERESOLVER_H

#include "IMessageResolver.h"
#include "IMessageCallback.h"

template<typename TMessage>
class MessageResolver : public IMessageResolver
{
	public:
		MessageResolver(IMessageCallback<TMessage> &callback)
			: m_callback(callback)
		{
		}

		quint8 type() const override
		{
			return TMessage::Type;
		}

		void resolve(QDataStream &stream, MessageWriter &writer) const override
		{
			TMessage message;

			stream >> message;

			m_callback.messageReceived(message, writer);
		}

	private:
		IMessageCallback<TMessage> &m_callback;
};

#endif // MESSAGERESOLVER_H
