#ifndef MEBBY_H
#define MEBBY_H

#include <QDataStream>
#include <QWebSocket>

class MessageWriter;

template<typename T>
class IMessageResolver
{
	public:
		virtual T type() const = 0;

		virtual void resolve(QDataStream &stream, MessageWriter &writer) const = 0;
};

template<auto TMessageType>
struct Message
{
	static const decltype(TMessageType) Type;
};

template <auto TMessageType>
const decltype(TMessageType) Message<TMessageType>::Type(TMessageType);

template<typename TMessage>
class MessageCallback
{
	public:
		virtual void messageReceived(const TMessage &message, MessageWriter &writer) = 0;
};

template<typename ...TMessage>
class MessageCallbacks : public MessageCallback<TMessage>...
{
};

template<typename T, typename TMessage>
class MessageResolver : public IMessageResolver<T>
{
	public:
		MessageResolver(MessageCallback<TMessage> &callback)
			: m_callback(callback)
		{
		}

		T type() const override
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
		MessageCallback<TMessage> &m_callback;
};

template<typename T>
class MessageRouter : public QObject
{
	public:
		template<typename ...TMessage>
		MessageRouter(MessageCallbacks<TMessage...> &callbacks)
			: m_resolvers({ new MessageResolver<T, TMessage>(callbacks)... })
		{
		}

		void onBinaryMessageReceived(MessageWriter &writer, const QByteArray &message)
		{
			std::underlying_type_t<T> messageType;

			QDataStream stream(message);
			stream >> messageType;

			for (IMessageResolver<T> *resolver : m_resolvers)
			{
				if (resolver->type() == static_cast<T>(messageType))
				{
					return resolver->resolve(stream, writer);
				}
			}
		}

	private:
		QList<IMessageResolver<T> *> m_resolvers;
};

class MessageWriter
{
	public:
		MessageWriter(QWebSocket *socket)
			: m_socket(socket)
		{
		}

		template<typename T>
		void write(const T &message)
		{
			QByteArray buffer;
			QDataStream stream(&buffer, QIODevice::WriteOnly);
			stream << T::Type;
			stream << message;

			m_socket->sendBinaryMessage(buffer);
		}

	private:
		QWebSocket *m_socket;
};

template<typename T>
class MessageRouterCallback
{
	public:
		MessageRouterCallback(QWebSocket *socket, MessageRouter<T> &messageFilter)
			: m_writer(socket)
			, m_messageFilter(messageFilter)
		{
		}

		void operator()(const QByteArray &message)
		{
			m_messageFilter.onBinaryMessageReceived(m_writer, message);
		}

	private:
		MessageWriter m_writer;
		MessageRouter<T> &m_messageFilter;
};

#endif // MEBBY_H
