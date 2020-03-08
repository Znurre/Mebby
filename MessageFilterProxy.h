#ifndef MESSAGEFILTERPROXY_H
#define MESSAGEFILTERPROXY_H

#include <QWebSocket>

#include "MessageFilter.h"
#include "MessageWriter.h"

class MessageFilterProxy
{
	public:
		MessageFilterProxy(QWebSocket *socket, MessageFilter &messageFilter)
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
		MessageFilter &m_messageFilter;
};

#endif // MESSAGEFILTERPROXY_H
