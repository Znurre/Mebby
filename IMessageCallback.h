#ifndef IMESSAGECALLBACK_H
#define IMESSAGECALLBACK_H

class MessageWriter;

template<typename TMessage>
class IMessageCallback
{
	public:
		virtual void messageReceived(const TMessage &message, MessageWriter &writer) = 0;
};

template<typename ...TMessage>
class IMessageCallbacks : public IMessageCallback<TMessage>...
{
};

#endif // IMESSAGECALLBACK_H
