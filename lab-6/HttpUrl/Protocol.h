#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol
{
public:
	static const Protocol HTTP;
	static const Protocol HTTPS;

	enum class Enum
	{
		HTTP = 0,
		HTTPS
	};

	Protocol();
	const char* ToString() const;
	operator Enum() const;

private:
	Protocol(Enum value);
	Enum m_value;
};

#endif // PROTOCOL_H