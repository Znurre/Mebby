#ifndef MESSAGEWRITER_H
#define MESSAGEWRITER_H

#include <QDataStream>
#include <QWebSocket>

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

#endif // MESSAGEWRITER_H
